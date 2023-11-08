
import json
from jinja2 import Template

# Assuming `json_data` is the input JSON as a string.
json_data = '''{
  {
      "table_name": "another_table_ver2",
      "columns": [
        {
          "name": "SHIP_NUMBER1",
          "type": "INT",
          "nullable": false,
          "primarykey": "PRIMARY KEY IDENTITY(1,1),"
        },
        {
          "name": "INV_PHASE_A_CURRENT",
          "type": "INT",
          "nullable": true
        },
        {
          "name": "INV_PHASE_B_CURRENT",
          "type": "INT",
          "nullable": true
        }
      ]
    }
}'''

# Parse the JSON input
data = json.loads(json_data)

# Define your Jinja2 template for the C++ function
cpp_template = '''
bool SendJsonToDb(nlohmann::json& jsonInput)
{
    //SP 방법 검토
    //동적 쿼리
    auto query = L"INSERT INTO [dbo].[{{ table_name }}]"
    L"("
    {% for column in columns %}
    L"[{{ column.name }}],"
    {% endfor %}
    L") VALUES ("
    {% for column in columns %}
    L"?,"
    {% endfor %}
    L")";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind<{{ bind_count }}, 0> dbBind(*dbConn, query);
    int32 count = 0;

    {% for column in columns %}
    {% if column.type == 'INT' %}
    int32 {{ column.name }} = jsonInput["{{ column.name }}"].get<int32>();
    dbBind.BindParam(count++, {{ column.name }});
    {% elif column.type == 'FLOAT' %}
    float {{ column.name }} = jsonInput["{{ column.name }}"].get<float>();
    dbBind.BindParam(count++, {{ column.name }});
    {% elif column.type == 'NVARCHAR' %}
    string {{ column.name }} = jsonInput["{{ column.name }}"].get<string>();
    wstring w{{ column.name }} = stringToWString({{ column.name }});
    WCHAR* pw{{ column.name }} = const_cast<WCHAR*>(w{{ column.name }}.c_str());
    dbBind.BindParam(count++, pw{{ column.name }});
    {% endif %}
    {% endfor %}

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    return true;
}
'''

# Prepare the context for the Jinja2 template
context = {
    'table_name': data['tables'][0]['table_name'],
    'columns': data['tables'][0]['columns'],
    'bind_count': sum(1 for _ in data['tables'][0]['columns'])
}

# Render the template with the context
template = Template(cpp_template)
cpp_code = template.render(context)

# Print or save the rendered C++ code
print(cpp_code)
