// import React, { SetStateAction, useCallback } from 'react';
// import { useContext } from 'react';
// import './App.css';
// import { UserMediaError, useUserMediaFromContext } from '@vardius/react-user-media';

// import { rsService } from './hooks/rsocketServiceHook';
// import { useState, useEffect } from 'react';
// import {tap, merge} from 'rxjs'
// import {useUserMedia} from "./getUserMedia"

//  function App() {
//   const myService = useContext(rsService);
//   const [data, setData] = useState<any | null> ();
//   const [userId, setUserId] = useState();  
//   const [msg, setMsg] = useState({});

//   const [vedio, setvedio] = useState();
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
//   // {
//   //   *    "id": "",
//   //   *    "vedioId" : ""
//   //   *    "rtmpUrls": [
//   //   *    "rtmp://localhost:1935/live/vedio"
//   //   *    ]
//   //   *    "params" : {
//   //   *      "passphrase or shomting this meant to be dynamic".
//   //   *     ...
//   //   *    }
 

//   useEffect(() => {
  
//     if (!connected)
//     {
//       myService.callRemoteAPI();
//       myService.send( null, "session");
      
//     }
//     else{
//         // stream?.addEventListener('addTrack',(e) => {
//         //   console.log(e);
//         // } );
//     }
//   },[connected]);

//   ;
//   const  readMessage = (msg:any) =>{
//     console.log(msg);
//     if (msg?.type?.toLowerCase() === "session")
//     {
//       setUserId (msg?.id);
//       console.log(msg?.id);
//       setConnected(true);
//     }
//     else if (msg?.type?.toLowerCase() === "vedio")
//       setData(msg?.data);
//   }


//   useEffect(()=>{
//     console.log("useEffect" + vedio + " " + userId);

//       myService.send(vedio,"vedio", userId);
//  });

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
//     },[connected]);

//   return (
//    <div>
//       <video src={data} autoPlay />
//     </div>
//   );
// }

// export default App;

import React, { useRef, useState } from 'react';
import  useUserMedia  from './getUserMedia';

const CAPTURE_OPTIONS = {
    audio: false,
    video: { facingMode: "environment" },
};

function App() {
  const videoRef = useRef();
  const mediaStream = useUserMedia(CAPTURE_OPTIONS);

  if (mediaStream && videoRef.current && !videoRef.current.srcObject) {
    videoRef.current.srcObject = mediaStream;
  }

  function handleCanPlay() {
    videoRef.current.play();
  }

  return (
    <video ref={videoRef} onCanPlay={handleCanPlay} autoPlay playsInline muted />
  );
}
export default App;