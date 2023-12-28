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
        _makeFunc.Add((ushort)EDT.EDT0001Enum.Battery, MakePacket<EDT0001.Battery>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.Battery_Pack, MakePacket<EDT0001.Battery_Pack>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_0, MakePacket<EDT0001.BAT_MODULE_0>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_1, MakePacket<EDT0001.BAT_MODULE_1>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_2, MakePacket<EDT0001.BAT_MODULE_2>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_3, MakePacket<EDT0001.BAT_MODULE_3>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.Environment, MakePacket<EDT0001.Environment>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.AIS, MakePacket<EDT0001.AIS>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.System_Time, MakePacket<EDT0001.System_Time>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.MOTOR, MakePacket<EDT0001.MOTOR>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.INVERTER, MakePacket<EDT0001.INVERTER>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.Network, MakePacket<EDT0001.Network>);
        _makeFunc.Add((ushort)EDT.EDT0001Enum.SaveAsBytes, MakePacket<EDT0001.SaveAsBytes>);
        _makeFunc.Add((ushort)EDT.MRSchemaEnum.C_Position, MakePacket<MRSchema.C_Position>);

        
        _handler.Add((ushort)EDT.EDT0001Enum.Battery, PacketHandler.Battery>);
        _handler.Add((ushort)EDT.EDT0001Enum.Battery_Pack, PacketHandler.Battery_Pack>);
        _handler.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_0, PacketHandler.BAT_MODULE_0>);
        _handler.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_1, PacketHandler.BAT_MODULE_1>);
        _handler.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_2, PacketHandler.BAT_MODULE_2>);
        _handler.Add((ushort)EDT.EDT0001Enum.BAT_MODULE_3, PacketHandler.BAT_MODULE_3>);
        _handler.Add((ushort)EDT.EDT0001Enum.Environment, PacketHandler.Environment>);
        _handler.Add((ushort)EDT.EDT0001Enum.AIS, PacketHandler.AIS>);
        _handler.Add((ushort)EDT.EDT0001Enum.System_Time, PacketHandler.System_Time>);
        _handler.Add((ushort)EDT.EDT0001Enum.MOTOR, PacketHandler.MOTOR>);
        _handler.Add((ushort)EDT.EDT0001Enum.INVERTER, PacketHandler.INVERTER>);
        _handler.Add((ushort)EDT.EDT0001Enum.Network, PacketHandler.Network>);
        _handler.Add((ushort)EDT.EDT0001Enum.SaveAsBytes, PacketHandler.SaveAsBytes>);
        _handler.Add((ushort)EDT.MRSchemaEnum.C_Position, PacketHandler.C_Position>);

        
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