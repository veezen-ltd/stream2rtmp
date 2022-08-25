import React, { useCallback, useContext, useEffect, useState } from "react";
import { Subject } from "rxjs";
import { setConstantValue } from "typescript";

import { rsService } from './hooks/rsocketServiceHook';
import { rsocketService } from './services/rsocketService';

export default function Consumer(
        onRecieve: any ,
        toSend: Subject<Blob>,
        // setConnected: any,
        ){
    const myService = useContext(rsService);
 const [userId, setUserId] = useState("");
 const [connected, setConnected] = useState(false);
 const [createSesssion, setCreateSession] = useState(false);
   
   const readMessage = (msg:any) =>{
        console.log(msg);
        if (msg?.type?.toLowerCase() === "session")
        {
          if (msg?.id !== null  && msg?.id?.length > 0)
            setUserId(msg.id);
          // console.log(msg?.id);
          // setConnected(true);
        }
        else if (msg?.type?.toLowerCase() === "stream")
        {
          // console.log(msg?.data);
          if (msg?.data !== null && msg?.data !== "")
            onRecieve(msg?.data);
        }
     }

     useEffect(() => {
        if (!connected)
        {
            myService.callRemoteAPI();
            if (!createSesssion)
            {
                             myService.send( null, "session");
                setCreateSession(true);
            }
                             setConnected(true);
        }
    
     },[connected, myService]);

    useCallback(() => {
        console.log("Consumer send data");
        toSend.subscribe(msg => myService.send(msg,"stream", userId) )
    }, [toSend, myService, userId]);
    
    useCallback(() => {
        console.log("Consumer read Data");
        myService?.remoteData$.subscribe(msg => 
            readMessage(msg));
    }, [myService, readMessage]);

    return <div>
        consumer
            </div>
}