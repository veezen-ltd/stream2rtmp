
import { Subject } from 'rxjs';
import {from } from 'rxjs';
import {tap} from 'rxjs/operators';
import { webSocket, WebSocketSubject } from 'rxjs/webSocket';
// import { WebSocket } from 'ws';

export class rsocketService {
  private _reset$ = new Subject<void>();
  private _remoteData$ = new Subject<any>();
  
    // Stream APIs
    public readonly reset$ = this._reset$.asObservable();
    public readonly remoteData$ = this._remoteData$.asObservable();

    private   address = {host: 'localhost', port: 8080};

    public  client: WebSocketSubject<any>;
    public  clientId: any;
   constructor() {
    this.client = webSocket(`ws://${this.address.host}:${this.address.port}`);
   }

private connect= () => {
     return this.client
         .asObservable();
}

public send(data: any , type: string, id: any = null) {
    console.log('send', data);
    this.client.next({data: data, type: type, id: id});
}


public reset = () => {
  this._reset$.next();
};

public callRemoteAPI = () => {
  from(this._fetchData())
    .pipe(
      tap({
        next: (resp) => this._remoteData$.next(resp),
        error: (err) => this._remoteData$.error(err),
      })
    )
    .subscribe();
};

private _fetchData = () => {

  // return the Promise the resolves the http call;
  console.log('calling remote api');
  return this.connect();
};

}
