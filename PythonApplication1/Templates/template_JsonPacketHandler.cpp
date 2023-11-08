void Send_{{table_name}}_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[{{ table_name }}]"
        L"("
    {%- for column in columns %}
    {%- if not column.primarykey %}
    L"[{{ column.name }}]"{{ ", " if not loop.last }};
    {%- endif %}
    {%- endfor %}
    L") VALUES (";
    {%- for column in columns %}
    {%- if not column.primarykey %}
    {{ "'?'" if not loop.last else "'?'" }};
    {%- endif %}
    {%- endfor %}
    L")";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind < {{ bind_count }}, 0 > dbBind(*dbConn, query);
    int32 count = 0;

    {%- for column in columns %}
    {%- if not column.primarykey %}
    {%- if column.type == 'INT'%}
    int32{{column.name}} = jsonInput["{{ column.name }}"].get<int32>();
    dbBind.BindParam(count++, &{{column.name}});
    {%- elif column.type == 'FLOAT'%}
    float{{column.name}} = jsonInput["{{ column.name }}"].get<float>();
    dbBind.BindParam(count++, &{{column.name}});
    {%- elif column.type == 'DOUBLE'%}
    double{{column.name}} = jsonInput["{{ column.name }}"].get<double>();
    dbBind.BindParam(count++, &{{column.name}});
    {%- elif column.type == 'NVARCHAR'%}
    std::string{{column.name}} = jsonInput["{{ column.name }}"].get<std::string>();
    std::wstring w{{column.name}} = stringToWString({{column.name}});
    WCHAR* pw{{column.name}} = const_cast<WCHAR*>(w{{column.name}}.c_str());
    dbBind.BindParam(count++, pw{{column.name}});
    {%- endif%}
    {%- endif%}
    {%- endfor%}

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    return true;
}
