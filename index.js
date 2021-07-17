const { Socket } = require('dgram');
const express=require('express')
const app=express();
const http=require('http')
const server=http.createServer(app)
const {Server}=require('socket.io')
const io=new Server(server)

//states od dustbins
let db1=1;
let db2=0;
let db3=0;

//number of sockets connected 
let no_webSoc=0;

function changeState(data1,data2,data3)
{
db1=data1
db2=data2
db3=data3
}

app.get('/', (req, res) => {
    console.log(`DUST_bin1:${(db1=='0')?"not_full":"full"}\nDUST_bin2:${(db2=='0')?"not_full":"full"}\nDUST_bin3:${(db3=='0')?"not_full":"full"}\n`)
    res.sendFile(__dirname + '/main.html')
  })

  app.get('/data',(req,res)=>{
    changeState(req.query.data[0],req.query.data[1],req.query.data[2])
    console.log(`>>DATA_UPDATE: STATES OF THE DUSTBINS ARE ${db1} ${db2} ${db3}`)
    io.emit('data',JSON.stringify([db1,db2,db3]))
    res.sendStatus(200)})
  



io.on('connect',(socket)=>{
  console.log(`>>WEB_SOCKET: ${++no_webSoc} webSockets client sconnected to server`)
  socket.on('disconnect',()=>{no_webSoc--})
  })

  server.listen(4000,()=>{
      console.log('BINARY DUSTBIN SERVER IS RUNNING ON PORT 4000')
  })

  app.get('/dustbin1',(req,res)=>{
  
    if(db1==1){
      res.sendFile(__dirname + '/trashb.svg');
    }
    else{
      
      res.sendFile(__dirname + '/trasha.svg');
     
    }
  })

  app.get('/dustbin2',(req,res)=>{
  
    if(db2==1){
      res.sendFile(__dirname + '/trashb.svg');
     
    }
    else{
      
      res.sendFile(__dirname + '/trasha.svg');
     
    }
  })

  app.get('/dustbin3',(req,res)=>{
    if(db3==1){
      res.sendFile(__dirname + '/trashb.svg');
    }
    else{
     
      res.sendFile(__dirname + '/trasha.svg');
     
    }
  })


  app.get('/college',(req,res)=>{
    res.sendFile(__dirname + '/college_logo.jpeg');
  })
  



