package jRPC

import (
	"github.com/Analyse4/ostep-hw/48/server/protocol"
    "github.com/Analyse4/ostep-hw/48/server/jRPC/stub"
)

// Send wrap with stub.send
func Send(msg *protocol.BaseMsg) *protocol.BaseMsg {
	return stub.Send(msg)
}