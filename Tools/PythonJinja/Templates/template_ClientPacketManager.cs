{# Jinja2 템플릿 코드 #}
{# 함수 정의: snake_case를 camelCase로 변환하는 필터 #}
{% macro snake_to_camel(value) %}
        {%- set parts = value.split('_') -%}
        {%- if parts | length > 1 -%}
            {{ parts[0] | capitalize }}
            {%- for part in parts[1:] -%}
                {{ part | capitalize }}
            {%- endfor -%}
        {%- else -%}
            {{ value }}
        {%- endif -%}
{%- endmacro -%}


using ServerCore;
using System;
using System.Collections.Generic;
using Google.Protobuf;

class ClientPacketManager
{
    #region Singleton
    static ClientPacketManager _instance = new ClientPacketManager();
    public static ClientPacketManager Instance { get { return _instance; } }
    #endregion

    ClientPacketManager()
    {
        Register();
    }

    Dictionary<ushort, Func<PacketSession, ArraySegment<byte>, IMessage>> _makeFunc = new Dictionary<ushort, Func<PacketSession, ArraySegment<byte>, IMessage>>();
    Dictionary<ushort, Action<ushort, PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<ushort, PacketSession, IMessage>>();

    public void Register()
    {

        {%- for idx in range(combined[1] | length) %}
        {%- for key in combined[2][idx] %}
        _makeFunc.Add((ushort){{package}}.{{combined[1][idx]}}Enum.{{ snake_to_camel(key)}}, MakePacket<{{ combined[1][idx]}}.{{key}}>);
        {%- endfor %}
        {%- endfor %}

        {% for idx in range(combined[1] | length) %}
        {%- for key in combined[2][idx] %}
        _handler.Add((ushort){{package}}.{{ combined[1][idx]}}Enum.{{snake_to_camel(key)}}, PacketHandler.{{key}}>);
        {%- endfor %}
        {%- endfor %}

        {% for package in packages %}
        {% for table in package['tables'] %}
        _makeFunc.Add((ushort){{ package['package']}}.{{package['package']}}
        Enum.{{table['table_name']}}, MakePacket <{{package['package']}}.{{ table['table_name']}});
        _handler.Add((ushort){{ package['package']}}.{{package['package']}}
        Enum.{{table['table_name']}}, PacketHandler.S_{{table['table_name']}});
        {% endfor %}
        {% endfor %}
    }

    public void OnRecvPacket(PacketSession session, ArraySegment<byte> buffer, Action<ushort, PacketSession, IMessage> onRecvCallback = null)
    {
        try
        {
            ushort count = 0;

            ushort protocolId = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
            count += 2;
            ushort size = BitConverter.ToUInt16(buffer.Array, buffer.Offset + count);
            count += 2;

            Func<PacketSession, ArraySegment<byte>, IMessage> func = null;
            if (_makeFunc.TryGetValue(protocolId, out func))
            {
                IMessage packet = func.Invoke(session, buffer);
                if (onRecvCallback != null)
                    onRecvCallback.Invoke(protocolId, session, packet);
                else
                    HandlePacket(protocolId, session, packet);
            }
        }
        #region exception
        catch (ArgumentException ex)
        {
            Console.WriteLine($"Argument Exception in OnRecvPacket: {ex}");
        }
        catch (InvalidCastException ex)
        {
            Console.WriteLine($"Invalid Cast Exception in OnRecvPacket: {ex}");
        }
        catch (OverflowException ex)
        {
            Console.WriteLine($"Overflow Exception in OnRecvPacket: {ex}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Unknown Exception in OnRecvPacket: {ex}");
            throw;
        }
        #endregion
    }

    T MakePacket<T>(PacketSession session, ArraySegment<byte> buffer) where T : IMessage, new()
    {
        T pkt = new T();
        pkt.MergeFrom(buffer.Array, buffer.Offset + 4, buffer.Count - 4);
        return pkt;
    }

    public void HandlePacket(ushort ProtocolId, PacketSession session, IMessage packet)
    {
        Action<ushort, PacketSession, IMessage> action = null;
        if (_handler.TryGetValue(ProtocolId, out action))
            action.Invoke(ProtocolId, session, packet);
    }
}
