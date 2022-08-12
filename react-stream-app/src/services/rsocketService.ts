
import { Subject } from 'rxjs';
import { Payload, ReactiveSocket} from 'rsocket-types';
import {from } from 'rxjs';
import {tap} from 'rxjs/operators';
import  { RSocketClient} from 'rsocket-core';
import RSocketWebsocketClient from 'rsocket-websocket-client';
// import RSocketTcpClient from 'rsocket-tcp-client';
import  WebsocketClientTransport  from "rsocket-websocket-client";
// import { WebSocket } from 'ws';
import { streamResponder } from './rsocketResponder';
import RsocketClient from '../RsocketClient';



export class rsocketService {
  private _reset$ = new Subject<void>();
  private _remoteData$ = new Subject<any>();
  
    // Stream APIs
    public readonly reset$ = this._reset$.asObservable();
    public readonly remoteData$ = this._remoteData$.asObservable();

    private   address = {host: '172.17.0.2', port: 9999};
    public  client: any;
    public  clientId: any;
   
private  getClientTransport(host: string, port: number) {
  return  new WebsocketClientTransport({
    url: "ws://" + host + ":" + port,
    wsCreator: (url: string) => new WebSocket(url) as any,
  })
}

private connect= (session: any, webCam:any): Promise<any> => {

  this.clientId = session['id'];
  console.log('clientId', this.clientId);
  this.client = new RSocketClient({
    setup: {
      // payload:
      // {
      //   data:JSON.stringify(session),
      //   metadata:'application/json'
      // },
      dataMimeType: 'plain/text',
      keepAlive: 60000,
      lifetime: 180000,
       metadataMimeType: 'plain/text',
    },
    responder: new streamResponder(webCam),
    transport: this.getClientTransport(this.address.host,
       this.address.port),
    }
  );
  console.log('client', this.client);
  return  new  Promise<any>((resolve, reject) => {
     this.client.connect()
    .subscribe({
      onError: console.log,
      onComplete: (rsocket:any) => {
        console.log("Success! We have established an RSocket connection.");
    },
      // onComplete:(socket: ReactiveSocket<any, any>)=> {
      //   socket.requestStream({
      //     data: this.clientId,
      //     metadata: '',
      //   })
      //   .subscribe({
      //     onNext:( response: Payload<any, any>) => {
      //       resolve(response.data);
      //       console.log('response', response);  
      //     },
      //     onError: console.log,
      //   })
      // },
    });
  });
}


public  logRequest(type: string, payload: Payload<string, string>) {
  console.log(`Responder response to ${type}, data: ${payload.data || 'null'}`);
}


public reset = () => {
  this._reset$.next();
};
public callRemoteAPI = (session: any, webCam:any) => {
  from(this._fetchData(session, webCam))

    .pipe(
      tap({
        next: (resp) => this._remoteData$.next(resp),
        error: (err) => this._remoteData$.error(err),
      })
    )
    .subscribe();
};

private _fetchData = (session: any, webCam:any): Promise<any> => {

  // return the Promise the resolves the http call;
  console.log('calling remote api');
  return this.connect(session, webCam);
};

};
