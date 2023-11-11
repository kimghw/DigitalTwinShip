import json
import os
from jinja2 import Environment, FileSystemLoader

current_dir = os.path.dirname(__file__)
parent_dir = os.path.abspath(os.path.join(current_dir, ".."))
pparent_dir = os.path.abspath(os.path.join(parent_dir, ".."))

# 파일을 읽고 JSON 데이터를 파싱하는 함수
def read_json_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        data = json.load(file)
    return data

# JSON 파일의 경로
file_path = os.path.join(pparent_dir, "GameServer", "DbSchema.json")
data = read_json_file(file_path)

# 환경변수 생성
env = Environment(loader=FileSystemLoader('.'))

# 함수 템플릿 갖어오기
Json_packetHandler_template = env.get_template('./templates/template_EDT0001_PacketHandler.cpp')
Json_packetHandler_template_h = env.get_template('./templates/template_EDT0001_PacketHandler.h')
protocol_template = env.get_template('./templates/template_Protocol.proto')
packetHandler_template = env.get_template('./templates/template_PacketHandler.h')

# 코드 렌더/만들기
json_packetHandler_rendered = Json_packetHandler_template.render(tables = data['tables'])
json_packetHandler_rendered_h = Json_packetHandler_template_h.render(tables = data['tables'])
Protocol_rendered = protocol_template.render(tables = data['tables'])
packetHandler_rendered = packetHandler_template.render(tables = data['tables'], Ship_num = data['Ship_num'])

# (JsonPacketHandler.cpp) 마지막으로 모든 렌더링된 함수를 하나의 파일에 저장합니다.

file_name = f'{data["Ship_num"]}_PacketHandler.cpp'
file_path = os.path.join(pparent_dir, "GameServer", file_name)
with open(file_path, 'w', encoding='utf-8') as file:
    file.write(json_packetHandler_rendered)
    print(f"Saved: {file_path}")
    
file_name = f'{data["Ship_num"]}_PacketHandler.h'
file_path = os.path.join(pparent_dir, "GameServer", file_name)
with open(file_path, 'w', encoding='utf-8') as file:
    file.write(json_packetHandler_rendered_h)
    print(f"Saved: {file_path}")

# (Protocol.proto) 마지막으로 모든 렌더링된 함수를 하나의 파일에 저장합니다.
file_name = f'{data["Ship_num"]}.proto'
file_path = os.path.join(parent_dir, "Protobuf", file_name)
with open(file_path, 'w', encoding='utf-8') as file:
    file.write(Protocol_rendered)
    print(f"Saved: {file_path}")

# (PacketHandler.h) 마지막으로 모든 렌더링된 함수를 하나의 파일에 저장합니다.
file_name = "ClientPacketHandler.h" 
file_path = os.path.join(pparent_dir, "GameServer", file_name)
with open(file_path, 'w', encoding='utf-8') as file:
    file.write(packetHandler_rendered)
    print(f"Saved: {file_path}")