import json
import os
from jinja2 import Environment, FileSystemLoader

# 파일을 읽고 JSON 데이터를 파싱하는 함수
def read_json_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        data = json.load(file)
    return data

# JSON 파일의 경로
file_path = '../GameServer/DBschema.json'  
data = read_json_file(file_path)

env = Environment(loader=FileSystemLoader('.'))

# 공통 헤더와 각 테이블 함수를 담을 문자열을 초기화합니다.
combined_rendered_functions = ""

# 공통 헤더 템플릿을 읽고 렌더링합니다.
common_header_template = env.get_template('template_common_header.cpp')
common_header_rendered = common_header_template.render()

# 렌더링된 공통 헤더를 추가합니다.
combined_rendered_functions += common_header_rendered + "\n\n"

# 함수 템플릿을 읽습니다.
template = env.get_template('template_JsonPacketHandler.cpp')

# 모든 테이블에 대한 함수를 생성하고 combined_rendered_functions에 추가합니다.
for table in data['tables']:
    rendered_function = template.render(
        table_name=table['table_name'],
        columns=table['columns'],
        bind_count=sum(1 for column in table['columns'] if not column.get('primarykey', False))
    )
    combined_rendered_functions += rendered_function + "\n\n"

# 마지막으로 모든 렌더링된 함수를 하나의 파일에 저장합니다.
filename = "JsonPacketHandler.cpp"
filepath = os.path.join("../GameServer", filename)
with open(filepath, 'w', encoding='utf-8') as file:
    file.write(combined_rendered_functions)
    print(f"Saved: {filepath}")
