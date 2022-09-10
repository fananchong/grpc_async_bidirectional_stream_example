package main

import (
	"client/test"
	"context"
	"flag"
	"fmt"
	"math/rand"
	"time"

	"google.golang.org/grpc"
)

var ip = flag.String("ip", "127.0.0.1", "ip address")
var port = flag.String("port", "22222", "port")
var clientNum = flag.Int("client_num", 500, "client num")
var data = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
var currentClientFlag = [10240]int{0}

type session struct {
	index  int
	stream test.TestService_StreamClient
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
			fmt.Printf("send msg = %v\n", msg)
			s.stream.SendMsg(msg)
		}
		// recv
		{
			msg := &test.Frame{}
			s.stream.RecvMsg(msg)
			v := msg.GetEcho().GetData()
			if v != data {
				panic(fmt.Sprintf("data error, send data: %v, recv data: %v", data, v))
			} else {
				fmt.Print(s.index, " ")
			}
		}

		// if rand.Int31n(100) <= 10 {
		// 	currentClientFlag[s.index] = 1
		// 	s.stream.CloseSend()
		// 	return
		// }

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
		stream, err := c.Stream(context.Background())
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
		// 	m = map[int]struct{}{}
		// 	for i := 0; i < *clientNum; i++ {
		// 		if currentClientFlag[i] != 0 {
		// 			currentClientFlag[i] = 0
		// 			m[i] = struct{}{}
		// 		}
		// 	}
		// 	if len(m) > 0 {
		// 		goto LABEL
		// 	}
		time.Sleep(10 * time.Millisecond)
	}
}
