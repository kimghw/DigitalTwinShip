import json
import re
import os
from jinja2 import Environment, FileSystemLoader

# 1. Read the DBScheme.json and MRSchema.json files
# 2. These contain the data structure of the all connected things
# 3. Abstract the table names from the json files


# 디렉토리 설정
current_dir = os.path.dirname(__file__)
parent_dir = os.path.abspath(os.path.join(current_dir, ".."))
pparent_dir = os.path.abspath(os.path.join(parent_dir, ".."))

# 파일을 읽고 JSON 데이터를 파싱하는 함수
def read_json_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        data = json.load(file)
    return data

# 템플릿 렌더링 결과를 파일로 저장하는 함수
def save_rendered_file(file_path, content):
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
    print(f"Saved: {file_path}")
    
# Jinja2 환경설정
env = Environment(loader=FileSystemLoader('.'))

# 템플릿 로드
#Template_Json_packetHandler = env.get_template('./templates/template_EDT0001_PacketHandler_OOP.cpp')
#Template_Json_packetHandler_h = env.get_template('./templates/template_EDT0001_PacketHandler_OOP.h')
#Template_message_protocol = env.get_template('./templates/template_protocol.proto')
#Template_enum_protocol = env.get_template('./templates/template_Enum.proto')
#Template_packetHandler_h= env.get_template('./templates/template_PacketHandler.h')
#Template_packetHandler_cs = env.get_template('./templates/template_ClientPacketManager.cs')

# Load the Json files which contains the data structure
file_path_DbSchema = os.path.join(pparent_dir, "GameServer", "DbSchema.json")
file_path_MRSchema = os.path.join(pparent_dir, "GameServer", "MRSchema.json")
data_DBSchema= read_json_file(file_path_DbSchema)
data_MRSchema = read_json_file(file_path_MRSchema)


# Abstrac the list of the talbe names and namespace of the all connected thins
## Old version
data_DBSchema_table_names = [table['table_name'] for table in data_DBSchema['tables']]
data_MRSchema_table_names = [table['table_name'] for table in data_MRSchema['tables']]
combined_enum1            = [data_DBSchema['enum'], data_DBSchema['package'], data_DBSchema_table_names]
combined_enum2            = [data_MRSchema['enum'], data_MRSchema['package'], data_MRSchema_table_names]
combined = list(zip(combined_enum1, combined_enum2))
## latest version
combined_list_data= [data_DBSchema, data_MRSchema]

# 함수 템플릿 갖어오기
Template_Json_packetHandler   = env.get_template('./templates/template_EDT0001_PacketHandler_OOP.cpp')
Template_Json_packetHandler_h = env.get_template('./templates/template_EDT0001_PacketHandler_OOP.h')
Template_message_protocol     = env.get_template('./templates/template_Protocol.proto')
Template_enum_protocol        = env.get_template('./templates/template_Enum.proto')
Template_packetHandler_h      = env.get_template('./templates/template_PacketHandler.h')
Template_packetHandler_cs     = env.get_template('./templates/template_ClientPacketManager.cs')

# 렌더링 하고 저장하기
# EDT는 동일 namespace를 갖게 해줄려고 공통적으로 넣어줌
Render_json_packetHandler = Template_Json_packetHandler.render(package =data_DBSchema['package'], tables = data_DBSchema['tables'], Ship_num = data_DBSchema['package'])
save_rendered_file(os.path.join(pparent_dir, "GameServer", f'{data_DBSchema["package"]}_PacketHandler.cpp'), Render_json_packetHandler)

Render_json_packetHandler_h = Template_Json_packetHandler_h.render(package =data_DBSchema['package'], tables = data_DBSchema['tables'], Ship_num = data_DBSchema['package'])
save_rendered_file(os.path.join(pparent_dir, "GameServer", f'{data_DBSchema["package"]}_PacketHandler.h'), Render_json_packetHandler_h)

Render_DbSchema_messasge_Protocol = Template_message_protocol.render(package = data_DBSchema['package'], tables = data_DBSchema['tables'])
save_rendered_file(os.path.join(parent_dir, "Protobuf", f'{data_DBSchema["package"]}.proto'), Render_DbSchema_messasge_Protocol)

Render_MRScheme_message_Protocol = Template_message_protocol.render(package = 'MRSchema', tables = data_MRSchema['tables'])
save_rendered_file(os.path.join(parent_dir, "Protobuf", f'{data_MRSchema["package"]}.proto'), Render_MRScheme_message_Protocol)

Render_enum_protocol = Template_enum_protocol.render(package = 'EDT', combined = combined)
save_rendered_file(os.path.join(parent_dir, "Protobuf", 'enum.proto'), Render_enum_protocol)

Render_Client_packetHandler_h = Template_packetHandler_h.render(type = 'Client', packages = combined_list_data)
save_rendered_file(os.path.join(pparent_dir, "GameServer", "ClientPacketHandler.h"), Render_Client_packetHandler_h)

Render_Server_packetHandler_h = Template_packetHandler_h.render(type = 'Server', packages = combined_list_data)
save_rendered_file(os.path.join(pparent_dir, "DummyClient", "ServerPacketHandler.h"), Render_Server_packetHandler_h)

Render_packetHandler_cs = Template_packetHandler_cs.render(package = 'EDT', combined = combined)
save_rendered_file(os.path.join(pparent_dir, "Csharp", 'ClientPacketManager.cs'), Render_packetHandler_cs)

