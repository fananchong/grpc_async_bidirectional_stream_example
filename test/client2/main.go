package main

import (
	"client2/test"
	"context"
	"flag"
	"fmt"
	"math/rand"
	"time"

	"google.golang.org/grpc"
)

var ip = flag.String("ip", "127.0.0.1", "ip address")
var port = flag.String("port", "22222", "port")
var clientNum = flag.Int("client_num", 50, "client num")
var data = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
var currentClientFlag = [10240]int{0}

type session struct {
	index  int
	stream test.TestService_Stream2Client
}

func (s *session) update() {
	for {
		// send
		{
			msg := &test.Frame{
				Msg: &test.Frame_Echo{
					Echo: &test.MsgEcho{
						Data: data,
					},
				},
			}
			s.stream.SendMsg(msg)
		}
		// recv #1
		{
			msg := &test.Frame{}
			s.stream.RecvMsg(msg)
			v := msg.GetEcho().GetData()
			if v != fmt.Sprintf("%v #1", data) {
				panic("data error")
			} else {
				fmt.Print(s.index, " ")
			}
		}

		// recv #2
		{
			msg := &test.Frame{}
			s.stream.RecvMsg(msg)
			v := msg.GetEcho().GetData()
			if v != fmt.Sprintf("%v #2", data) {
				panic("data error")
			} else {
				fmt.Print(s.index, " ")
			}
		}

		// recv #3
		{
			msg := &test.Frame{}
			s.stream.RecvMsg(msg)
			v := msg.GetEcho().GetData()
			if v != fmt.Sprintf("%v #3", data) {
				panic("data error")
			} else {
				fmt.Print(s.index, " ")
			}
		}

	}
}

func main() {
	flag.Parse()

	conn, err := grpc.Dial(fmt.Sprintf("%s:%s", *ip, *port), grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		fmt.Printf("conn server failed, err:%v\n", err)
		return
	}

	rand.Seed(time.Now().UnixNano())

	m := map[int]struct{}{}
	for i := 0; i < *clientNum; i++ {
		m[i] = struct{}{}
	}

	// LABEL:
	for i := range m {
		c := test.NewTestServiceClient(conn)
		stream, err := c.Stream2(context.Background())
		if err != nil {
			fmt.Printf("conn server failed, err:%v\n", err)
			return
		}
		sess := &session{
			index:  i,
			stream: stream,
		}
		go sess.update()
	}

	for {
		time.Sleep(10 * time.Millisecond)
	}
}
