# PythonJinja - 네트워크 코드 자동 생성 도구

Jinja2 템플릿 엔진을 사용하여 JSON 스키마로부터 네트워크 프로토콜 및 패킷 핸들러 코드를 자동 생성하는 도구입니다.

## � 작동 원리

```
📥 INPUT (읽기)
   ├─ C:\...\UWP_Network\GameServer\DbSchema.json
   └─ C:\...\UWP_Network\GameServer\MRSchema.json
          ↓
   🔧 PROCESSING (Jinja2 템플릿 렌더링)
          ↓
📤 OUTPUT (생성)
   ├─ C:\...\UWP_Network\GameServer\
   │    ├─ EDT0001_PacketHandler.cpp    ← JSON → Protobuf 변환, DB INSERT
   │    ├─ EDT0001_PacketHandler.h      ← 패킷 핸들러 클래스 정의
   │    └─ ClientPacketHandler.h        ← 클라이언트 패킷 라우팅
   │
   ├─ C:\...\UWP_Network\Tools\Protobuf\
   │    ├─ EDT0001.proto                ← DB 스키마 → Protobuf 메시지
   │    ├─ MRSchema.proto               ← MR 스키마 → Protobuf 메시지
   │    └─ enum.proto                   ← 패킷 ID enum 정의
   │
   └─ C:\...\UWP_Network\DummyClient\
        └─ ServerPacketHandler.h        ← 서버 패킷 라우팅
```

### 처리 과정
1. **JSON 스키마 읽기**: GameServer 폴더에서 스키마 파일 로드
2. **템플릿 적용**: Templates 폴더의 Jinja2 템플릿으로 코드 생성
3. **파일 저장**: 생성된 코드를 각 프로젝트 폴더에 배치
4. **자동 통합**: 생성된 파일들이 즉시 프로젝트에 통합 가능

## �📋 목차
- [개요](#개요)
- [주요 기능](#주요-기능)
- [설치 방법](#설치-방법)
- [사용법](#사용법)
- [생성되는 파일](#생성되는-파일)
- [템플릿 구조](#템플릿-구조)
- [스키마 형식](#스키마-형식)

## 🎯 개요

데이터베이스 스키마가 변경될 때마다 네트워크 프로토콜과 패킷 핸들러 코드를 수동으로 수정하는 번거로움을 제거합니다. JSON 스키마 파일만 수정하면 전체 네트워크 레이어 코드가 자동으로 생성됩니다.

## ✨ 주요 기능

- **JSON → Protocol Buffers**: 데이터베이스 스키마를 `.proto` 파일로 자동 변환
- **C++ 패킷 핸들러 생성**: 클라이언트/서버 패킷 처리 코드 자동 생성
- **OOP 스타일 코드**: Protocol Buffer를 활용한 객체 지향 패킷 핸들러
- **DB 연동 코드**: 자동으로 데이터베이스 INSERT 쿼리 생성
- **타입 안전성**: JSON 검증 및 타입 체크 로직 포함

## 📦 설치 방법

### 필수 요구사항
- Python 3.7 이상
- Jinja2 라이브러리

### 설치
```bash
pip install jinja2
```

## 🚀 사용법

### 1. JSON 스키마 파일 준비

`GameServer` 폴더에 다음 파일들이 있어야 합니다:
- `DbSchema.json` - 데이터베이스 스키마
- `MRSchema.json` - 메모리 레지스터 스키마

### 2. 실행

```bash
cd C:\Users\USER\source\repos\UWP_Network\Tools\PythonJinja
python PythonJinja.py
```

### 3. 결과 확인

생성된 파일들이 지정된 위치에 자동으로 저장됩니다.

## 📁 생성되는 파일

### 1. GameServer 폴더 (`../../GameServer/`)
- `{package}_PacketHandler.cpp` - 패킷 핸들러 구현 (OOP)
- `{package}_PacketHandler.h` - 패킷 핸들러 헤더 (OOP)
- `ClientPacketHandler.h` - 클라이언트 패킷 처리

### 2. Protobuf 폴더 (`../Protobuf/`)
- `{package}.proto` - Protocol Buffer 메시지 정의
- `MRSchema.proto` - 메모리 레지스터 프로토콜
- `enum.proto` - 패킷 ID enum 정의

### 3. DummyClient 폴더 (`../../DummyClient/`)
- `ServerPacketHandler.h` - 서버 패킷 처리

## 📂 템플릿 구조

### 활성 템플릿 (Templates 폴더)
```
Templates/
├── template_EDT0001_PacketHandler_OOP.cpp   # C++ 패킷 핸들러 구현
├── template_EDT0001_PacketHandler_OOP.h     # C++ 패킷 핸들러 헤더
├── template_Protocol.proto                  # Protobuf 메시지 템플릿
├── template_Enum.proto                      # Enum 정의 템플릿
└── template_PacketHandler.h                 # 범용 패킷 핸들러 템플릿
```

### 템플릿 기능

#### 1. `template_EDT0001_PacketHandler_OOP.cpp/h`
- JSON 파싱 및 검증
- JSON → Protocol Buffer 변환
- Protocol Buffer → DB INSERT 쿼리 자동 생성
- 예외 처리 포함

#### 2. `template_Protocol.proto`
- 테이블 구조를 Protobuf 메시지로 변환
- 타입 매핑 (INT, FLOAT, DOUBLE, NVARCHAR 등)
- repeated 필드 지원

#### 3. `template_Enum.proto`
- 패킷 ID enum 생성
- 네임스페이스별 enum 정의

#### 4. `template_PacketHandler.h`
- 클라이언트/서버 패킷 라우팅
- 패킷 직렬화/역직렬화
- 핸들러 함수 자동 등록

## 📄 스키마 형식

### JSON 스키마 구조 예시

```json
{
  "package": "EDT0001",
  "enum": "EDT0001Enum",
  "tables": [
    {
      "table_name": "BatteryStatus",
      "columns": [
        {
          "name": "id",
          "type": "INT",
          "primarykey": true,
          "repeated": false
        },
        {
          "name": "voltage",
          "type": "FLOAT",
          "primarykey": false,
          "repeated": false
        },
        {
          "name": "description",
          "type": "NVARCHAR",
          "primarykey": false,
          "repeated": false
        }
      ]
    }
  ]
}
```

### 지원되는 데이터 타입
- `INT` → `int32` (Protobuf)
- `FLOAT` → `float` (Protobuf)
- `DOUBLE` → `double` (Protobuf)
- `NVARCHAR` → `string` (Protobuf)
- `BYTE` → `bytes` (Protobuf)

### 필수 필드
- `package`: 패키지/네임스페이스 이름
- `enum`: enum 타입 이름
- `tables`: 테이블 배열
  - `table_name`: 테이블 이름
  - `columns`: 컬럼 배열
    - `name`: 컬럼 이름
    - `type`: 데이터 타입
    - `primarykey`: Primary Key 여부
    - `repeated`: 배열 타입 여부

## 🔄 워크플로우

```
JSON 스키마 수정
    ↓
PythonJinja.py 실행
    ↓
템플릿 렌더링
    ↓
자동 생성된 코드
    ↓
프로젝트에 통합
```

## 📝 주의사항

1. **기존 파일 덮어쓰기**: 생성된 파일이 이미 존재하면 덮어씁니다.
2. **수동 수정 금지**: 생성된 파일을 직접 수정하지 마세요. 스키마를 수정하고 재생성하세요.
3. **백업 권장**: 중요한 변경 전에는 백업을 권장합니다.
4. **경로 확인**: 상대 경로가 올바른지 확인하세요 (`parent_dir`, `pparent_dir`).

## 🛠 커스터마이징

### 새 템플릿 추가
1. `Templates/` 폴더에 `.jinja2` 또는 적절한 확장자로 템플릿 생성
2. `PythonJinja.py`에서 템플릿 로드:
   ```python
   Template_new = env.get_template('./templates/template_new.ext')
   ```
3. 렌더링 및 저장:
   ```python
   Render_new = Template_new.render(data=your_data)
   save_rendered_file(output_path, Render_new)
   ```

### 템플릿 문법
Jinja2 템플릿 문법 사용:
- 변수: `{{ variable }}`
- 반복문: `{% for item in items %} ... {% endfor %}`
- 조건문: `{% if condition %} ... {% endif %}`
- 필터: `{{ value|lower }}`, `{{ value|upper }}`

## 📞 문의

프로젝트 관련 문의사항이나 버그 리포트는 이슈 트래커를 이용해주세요.

## 📜 라이선스

이 프로젝트의 라이선스는 별도로 명시되어 있지 않습니다.
