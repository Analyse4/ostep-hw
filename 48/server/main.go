package main

import (
	"fmt"

	"github.com/Analyse4/ostep-hw/48/server/jRPC"
	"github.com/Analyse4/ostep-hw/48/server/protocol"
)

func main() {
	fmt.Println("server start")
	req := new(protocol.BaseMsg)
	req.ID = 1
	req.Msg = []byte("req")
	ack := jRPC.Send(req)
	fmt.Println(ack)
}
