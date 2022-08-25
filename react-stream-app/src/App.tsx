// import React, { SetStateAction, useCallback } from 'react';
// import { useContext } from 'react';
// import './App.css';
// import { UserMediaError, useUserMediaFromContext } from '@vardius/react-user-media';

// import { rsService } from './hooks/rsocketServiceHook';
// import { useState, useEffect } from 'react';
// import {tap, merge} from 'rxjs'
// import { Stream } from 'stream';


//  function App() {

//   const [data, setData] = useState<any | null> ();
//   const [userId, setUserId] = useState();  
//   const [vedio, setvedio] = useState(
//   ""
//   );
//   const [connected, setConnected] = useState(false);
//   const [session, setSession] = useState({
//     id: "557b39c4-305e-4495-b27c-9bd2e277ad70",
//     vedioId:"557b39c4-305e-4495-b27c-9bd2e277ad71",
//     rtmpUrls: [
//       "rtmp://localhost:1935/live/vedio"
//     ],
//     params:{
//       "passphrase":"1234567890",
//     },
//   });

//   const CAPTURE_OPTIONS = {
//     audio: false,
//     video: { facingMode: "environment" },
//   };

 
//  async function start() {
//    let stream =  await navigator.mediaDevices
//     .getUserMedia(CAPTURE_OPTIONS);
//     const  rec =  new MediaRecorder(stream, { mimeType: "video/webm" });


//     rec.start(2000);
//     rec.ondataavailable = (e) => {
//     e.data.text()
//  .then(data => {
//     setvedio(data);
//   }).catch(err => {
//     console.log(err);
  

//   })
//   }
// }


//   useEffect(() => {
  
//     if (!connected)
//     {
//       myService.callRemoteAPI();
//       myService.send( null, "session");
      
//     }
//     else{
//       start();
//         // stream?.addEventListener('addTrack',(e) => {
//         //   console.log(e);
//         // } );
//     }
//   },[start, myService,connected]);




//   useEffect(()=>{
//    // console.log("useEffect" + vedio + " " + userId);

//      myService.send(vedio,"stream", userId);
//  }, [vedio]);

//   useEffect(() => {

   

//       const data$ = myService.remoteData$.pipe(
//         tap((data) => readMessage(data))
//       );
//       const reset$ = myService.reset$.pipe(
//         tap((data) => setData(""))
//       );
//         const sub = merge(data$, reset$).subscribe();
//         console.log(connected);
//       // const subscription = merge(data$, reset$).subscribe();
    

//       // fetch('http://localhost:8080/session',{
//       //   method: "POST",
//       //   headers: {
//       //     "access-control-allow-origin" : "*",
//       //     "Content-type": "application/json; charset=UTF-8"
//       //   }})
      
//       // .then(res=> res.json().then(data => setSession(data)))
//       // .then(()=>{
//       //   myService.callRemoteAPI(session,vedio);
//       // }).catch(err=>console.log(err));
//       // setSession([{"id":"557b39c4-305e-4495-b27c-9bd2e277ad70",
//       // "sessionId":"ecbecb40-00e3-4a65-bb7a-28cdb9822033",
//       // "passphrase":"7d05d131-775f-4fc2-8412-659a6823dd98",
//       // "createdAt":"2022-08-10T18:08:49.320801249",
//       // "endAt":null,"objectId":null}])

//       // return () => {
//       //   subscription.unsubscribe();
//       // };
//      // 
//     },[myService ,connected]);

//   return (
//    <div>
      
//     </div>
//   );
// }

// export default App;
/* eslint-env browser */
import React from 'react';
import { useContext } from 'react';
import { Subject } from 'rxjs';
import Consumer from './Consumer'

const audioType = 'audio/*';

class App extends React.Component<{},{recording : boolean, connect: boolean, userId: string, data : Blob}> {
   video: any ;
   mediaRecorder: MediaRecorder | null;
   toSend : Subject<Blob>;
  constructor(props : any) {
    super(props);
    this.state = {
       recording: false,
        connect: false,
        userId: "",
        data: new Blob(),
    };
    this.mediaRecorder = null;
    this.toSend = new Subject<any>();
  }

  async componentDidMount() {
    const stream = await navigator.mediaDevices.getUserMedia({audio: true});
    // show it to user
    this.video.srcObject = stream.clone();
    this.video.play();
    // init recording
    this.mediaRecorder = new MediaRecorder(stream);
    // init data storage for video chunks
    // listen for data from media recorder
    this.mediaRecorder.ondataavailable = e => {
      if (e.data && e.data.size > 0) {
        // send data to server
        // this.chunks.push(e.data);
        // this.myService?.send(e.data, "stream", this.state.userId);
        this.toSend.next(e.data);
      }
    };
  }
  
  startRecording(e: any) {
    e.preventDefault();
    // wipe old data chunks
    // this.chunks = [];
    // start recorder with 10ms buffer
    this.mediaRecorder?.start(10);
    // say that we're recording
    this.setState({recording: true});
  }

  stopRecording(e: any) {
    e.preventDefault();
    // stop the recorder
    this.mediaRecorder?.stop();
    // say that we're not recording
    this.setState({recording: false});
    // save the video to memory
    //this.saveAudio();
  }

  connect(e: any) {
    e.preventDefault();
    this.setState({connect: true});
//    this.myService.remoteData$.subscribe(data => this.readMessage(data));
  }
  
  disconnect(e: any) {
    e.preventDefault();
    this.stopRecording(e);
    this.setState({connect: false});
  }

  onRecieved(data : Blob) {
    this.video.srcObject.addTrack(data);
  }


  render() {
     

    return (
      <div className="camera">
        <video autoPlay playsInline ref={video => 
          this.video = video} />
         
          <div>
            {!this.state.connect  
            && <button onClick={e => this.connect(e)}> connect</button>}
            {this.state.connect && <button onClick={e => this.disconnect(e)}> disconnect</button>}
          </div>

        <div>
          {!this.state.recording && <button onClick={e => this.startRecording(e)}>Record</button>}
          {this.state.recording && <button onClick={e => this.stopRecording(e)}>Stop</button>}
        </div>
         <Consumer toSend={this.toSend} onRecieved = {this.onRecieved}></Consumer>
      </div>
    );
  }
}
export default App;
