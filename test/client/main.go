package main

import (
	"client/test"
	"context"
	"flag"
	"fmt"
	"math/rand"
	"strconv"
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
			// fmt.Printf("send msg = %v\n", msg)
			fmt.Printf(".")
			s.stream.SendMsg(msg)
		}
		// recv
		{
			msg := &test.Frame{}
			err := s.stream.RecvMsg(msg)
			if err != nil {
				panic(err)
			}
			v := msg.GetEcho().GetData()
			if v != data {
				panic(fmt.Sprintf("data error, send data len: %v, recv data len: %v", len(data), len(v)))
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

	conn, err := grpc.Dial(fmt.Sprintf("%s:%s", *ip, *port), grpc.WithInsecure(), grpc.WithBlock(),
		grpc.WithInitialWindowSize(int32(8*1024*1024)),
		grpc.WithReadBufferSize(4*1024*1024),
		grpc.WithWriteBufferSize(4*1024*1024),
		grpc.WithDefaultCallOptions(grpc.MaxCallRecvMsgSize(128*1024*1024)),
		grpc.WithDefaultCallOptions(grpc.MaxCallSendMsgSize(128*1024*1024)),
	)
	if err != nil {
		fmt.Printf("conn server failed, err:%v\n", err)
		return
	}

	rand.Seed(time.Now().UnixNano())

	m := map[int]struct{}{}
	for i := 0; i < *clientNum; i++ {
		m[i] = struct{}{}
	}

	var tmp string
	for i := 0; i < 10000; i++ {
		tmp += strconv.Itoa(i)
	}
	for i := 0; i < 1000; i++ {
		data += string(tmp)
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
