import React from 'react';
import { useContext } from 'react';
import './App.css';

import { rsService } from './hooks/rsocketServiceHook';
import { useState, useEffect } from 'react';
import {tap, merge} from 'rxjs'

 function App() {
  const myService = useContext(rsService);
  const [data, setData] = useState("No data received yet from remote service");  
  const [stream, setStream] = useState();
  const [session, setSession] = useState({
    id: "557b39c4-305e-4495-b27c-9bd2e277ad70",
    streamId:"557b39c4-305e-4495-b27c-9bd2e277ad71",
    rtmpUrls: [
      "rtmp://localhost:1935/live/stream"
    ],
    params:{
      "passphrase":"1234567890",
    },
  });
  // {
  //   *    "id": "",
  //   *    "streamId" : ""
  //   *    "rtmpUrls": [
  //   *    "rtmp://localhost:1935/live/stream"
  //   *    ]
  //   *    "params" : {
  //   *      "passphrase or shomting this meant to be dynamic".
  //   *     ...
  //   *    }

  useState(() => {
    let newVariable: any;

    newVariable = window.navigator;
    if (newVariable.getUserMedia) {
      newVariable.getUserMedia(
        { video: true },
        setStream,
        console.log
      );
    }
    myService.callRemoteAPI(session,stream);

  });
  useEffect(() => {

   

      const data$ = myService.remoteData$.pipe(
        tap((data) => setData(data))
      );
      const reset$ = myService.reset$.pipe(
        tap((data) => setData(""))
      );
  
      const subscription = merge(data$, reset$).subscribe();
    

      // fetch('http://localhost:8080/session',{
      //   method: "POST",
      //   headers: {
      //     "access-control-allow-origin" : "*",
      //     "Content-type": "application/json; charset=UTF-8"
      //   }})
      
      // .then(res=> res.json().then(data => setSession(data)))
      // .then(()=>{
      //   myService.callRemoteAPI(session,stream);
      // }).catch(err=>console.log(err));
      // setSession([{"id":"557b39c4-305e-4495-b27c-9bd2e277ad70",
      // "sessionId":"ecbecb40-00e3-4a65-bb7a-28cdb9822033",
      // "passphrase":"7d05d131-775f-4fc2-8412-659a6823dd98",
      // "createdAt":"2022-08-10T18:08:49.320801249",
      // "endAt":null,"objectId":null}])

      // return () => {
      //   subscription.unsubscribe();
      // };
     // 
      return () => {
        subscription.unsubscribe();
      }
    }, [myService, session, stream]);

  return (
   <div>
      <video src={data} autoPlay= {true} />
    </div>
  );
}

export default App;
