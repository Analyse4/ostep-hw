package stub

import "github.com/Analyse4/ostep-hw/48/server/protocol"

func Send(msg *protocol.BaseMsg) *protocol.BaseMsg {
	ack := new(protocol.BaseMsg)
	ack.ID = 2
	ack.Msg = []byte("ack")
	return ack
}
