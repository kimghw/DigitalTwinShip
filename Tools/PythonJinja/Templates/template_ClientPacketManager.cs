using ServerCore;
using System;
using System.Collections.Generic;
using Google.Protobuf;

class PacketManager
{
    #region Singleton
    static PacketManager _instance = new PacketManager();
    public static PacketManager Instance { get { return _instance; } }
    #endregion

    PacketManager()
    {
        Register();
    }

    Dictionary<ushort, Func<PacketSession, ArraySegment<byte>, IMessage>> _makeFunc = new Dictionary<ushort, Func<PacketSession, ArraySegment<byte>, IMessage>>();
    Dictionary<ushort, Action<ushort, PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<ushort, PacketSession, IMessage>>();

    public void Register()
    {

        {%- for idx in range(combined[1] | length) %}
        {%- for key in combined[2][idx] %}
        _makeFunc.Add((ushort){{package}}.{{combined[1][idx]}}Enum.{{key}}, MakePacket<{{ combined[1][idx]}}.{{key}}>);
        {%- endfor %}
        {%- endfor %}

        {% for idx in range(combined[1] | length) %}
        {%- for key in combined[2][idx] %}
        _handler.Add((ushort){{package}}.{{ combined[1][idx]}}Enum.{{key}}, PacketHandler.{{key}}>);
        {%- endfor %}
        {%- endfor %}

        {% for package in packages %}
        {% for table in package['tables'] %}
        _makeFunc.Add((ushort){ { package['package']} }.{ { package['package']} }
        Enum.{ { table['table_name']} }, MakePacket <{ { package['package']} }.{ { table['table_name']} });
        _handler.Add((ushort){ { package['package']} }.{ { package['package']} }
        Enum.{ { table['table_name']} }, PacketHandler.S_{ { table['table_name']} });
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