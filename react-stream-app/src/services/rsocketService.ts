
import { Frame } from 'rsocket-types';
import {Responder, Payload} from 'rsocket-types';
import  {Leases, Lease, RSocketClient} from 'rsocket-core';
import {Flowable, Single, every} from 'rsocket-flowable';
import RSocketTcpClient from 'rsocket-tcp-client';


export class rsocketService {
    private _reset$ = Single<void>.never();
    private _remoteData$ =  Flowable<Frame>.just(null);
  
    // Stream APIs
    public readonly reset$ = this._reset$;
    public readonly remoteData$ = this._remoteData$;

    private   address = {host: '127.0.0.1', port: 9898};

    private client: RSocketTcpClient;
//  make(data: string, metadata: string): Payload<string, string> {
//   return {
//     data,
//     metadata: metadata,
//   };
// }



public  logRequest(type: string, payload: Payload<string, string>) {
  console.log(`Responder response to ${type}, data: ${payload.data || 'null'}`);
}

// class EchoResponder implements Responder<string, string> {
//   requestResponse(payload: Payload<string, string>): Single<Payload<string, string>> {
//     throw new Error('Method not implemented.');
//   }
//   requestStream(payload: Payload<string, string>): Flowable<Payload<string, string>> {
//     throw new Error('Method not implemented.');
//   }
//   requestChannel(payloads: Flowable<Payload<string, string>>): Flowable<Payload<string, string>> {
//     throw new Error('Method not implemented.');
//   }
//   metadataPush(payload: Payload<string, string>): Single<void> {
//     return Single.error(new Error('not implemented'));
//   }

//   fireAndForget(payload: Payload<string, string>): void {
//     logRequest('fire-and-forget', payload);
//   }

//   // requestResponse(
//   //   payload: Payload<string, string>,
//   // ): Single<Payload<string, string>> {
//   //   logRequest('request-response', payload);
//   //   return Single.of(make('client response'));
//   // }

//   // requestStream(
//   //   payload: Payload<string, string>,
//   // ): Flowable<Payload<string, string>> {
//   //   logRequest('request-stream', payload);
//   //   return Flowable.just(make('client stream response'));
//   // }

//   // requestChannel(
//   //   payloads: Flowable<Payload<string, string>>,
//   // ): Flowable<Payload<string, string>> {
//   //   return Flowable.just(make('client channel response'));
//   // }
// }

private  getClientTransport(host: string, port: number) {
  return new RSocketTcpClient({
    host,
    port,
  });

}


public   connectRsocket()
{
 this.client = new RSocketClient({
    setup: {
    
      dataMimeType: 'text/plain',
      keepAlive: 1000000,
      lifetime: 100000,
      metadataMimeType: 'text/plain',
      payload: {
        metadata: 'Application/json',
        // data: JSON.stringify(userInfo)
      },
      
    },
    // responder: new EchoResponder(),
    // leases: () =>
    //   new Leases()
    //     .receiver(receivedLeasesLogger)
    //     .sender(stats => periodicLeaseSender(10000, 7000, 10)),
    transport: this.getClientTransport(this.address.host, this.address.port),
  })
}
  
    // Method APIs
    public reset = () => {
      this._reset$.then();
    };


    // public getStream = (client:  ) => 
    // {
    //     // client..subscribe({
    //     //     onNext: (payload) => {
    //     //         this._remoteData$.next(payload);
    //     //     }
    //     // });
    // }
    // public callRemoteAPI = (input: string) => {
    //   from(this._fetchData(input))
    //     .pipe(
    //       tap({
    //         next: (resp) => this._remoteData$.next(resp),
    //         error: (err) => this._remoteData$.error(err),
    //       })
    //     )
    //     .subscribe();
    // };
  
    // private _fetchData = (input: string): Promise<string> => {
    //   // return the Promise the resolves the http call;
    // };
  };
