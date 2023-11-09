void Send_{{table_name}}_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[{{table_name}}]"
    L"("
    {%- for column in columns%}
    {%- if not column.primarykey%}
    L"[{{column.name}}]{{ "," if not loop.last else "" }}"
    {%- endif%}
    {%- endfor%}
    L")"
    L"VALUES(
    {%- for column in columns -%}
    {%- if not loop.last -%}
    {{ "?," if loop.revindex > 2 else "" }}
    {%- else -%}
    {{ "?" if loop.revindex > 1 else "?"}}
    {%- endif -%}
    {%- endfor -%}
    );";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <{{bind_count}},0> dbBind(*dbConn, query);
    int32 count = 0;
    {% set ns = namespace(Number = 1)%}
    {%- for column in columns%}
    {%- if not column.primarykey%}
    // {{ ns.Number }}. {{ column.name }} to Database
    //     Table name : {{table_name}}, Column name : {{column.name}}, Type : {{column.type}}
    {%- if column.type == 'INT'%}
    int32 {{ column.name }} = 0;
    try {
        {{ column.name }} = jsonInput["{{ column.name }}"].get<int32>();
        dbBind.BindParam(count++,{{ column.name }});
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key '{{ column.name }}' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,{{ column.name }});
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in '{{ column.name }}' value:" << e.what() << '\n';
        dbBind.BindParam(count++,{{column.name}});
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,{{ column.name }});
    }

    {%- elif column.type == 'FLOAT'%}
    float{{ column.name }} = 0.0;
    try {
        {{column.name}} = jsonInput["{{column.name}}"].get<float>();
        dbBind.BindParam(count++,{{column.name}});
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key '{{ column.name }}' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++,{{ column.name }});
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in '{{ column.name }}' value: " << e.what() << '\n';
        dbBind.BindParam(count++,{{column.name}});
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,{{ column.name }});
    }

    {%- elif column.type == 'DOUBLE'%}
    double {{ column.name }} = 0.0;
    try {
    {{column.name}} = jsonInput["{{column.name}}"].get<double>();
    dbBind.BindParam(count++, {{column.name}});
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key '{{ column.name }}' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, {{ column.name }});
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in '{{ column.name }}' value: " << e.what() << '\n';
        dbBind.BindParam(count++, {{column.name}});
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, {{ column.name }});
    }

    {%- elif column.type == 'NVARCHAR'%}
    std::wstring w{{column.name}} = L"No input";
    WCHAR* pw{{ column.name }} = nullptr;
    try {
        std::string {{column.name}} = jsonInput["{{column.name}}"].get<std::string>();
        w{{column.name}} = stringToWString({{column.name}});
        pw{{column.name}} = const_cast<WCHAR*>(w{{column.name}}.c_str());
        dbBind.BindParam(count++, pw{{column.name}});
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key '{{ column.name }}' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pw{{ column.name }});
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in '{{ column.name }}' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pw{{column.name}});
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pw{{ column.name }});
    }
    {%- endif%}
    {%- endif%}
    {%- endfor%}

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

