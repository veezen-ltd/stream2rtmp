import {Responder, Payload} from 'rsocket-types'
import {Flowable, Single, every} from 'rsocket-flowable';

export class streamResponder implements Responder<any, any> {
    private webCam: any;

    constructor(webCam: any) {
        this.webCam  = webCam;
    }
    metadataPush(payload: Payload<any, any>): Single<void> {
        return Single.error(new Error('not implemented'));
      }
    
      fireAndForget(payload: Payload<any, any>): void {
        //logRequest('fire-and-forget', payload);
      }
    
      requestResponse(
        payload: Payload<any, any>,
      ): Single<Payload<any, any>> {
       // logRequest('request-response', payload);
        return Single.error(new Error('not implemented'));
      }
    
      requestStream(
        payload: Payload<any, any>,
      ): Flowable<Payload<any, any>> {
        // logRequest('request-stream', payload);
        // return Flowable.just(make('client stream response'));
        return this.webCam;
      }
    
      requestChannel(
        payloads: Flowable<Payload<any, any>>,
      ): Flowable<Payload<any, any>> {
        // return Flowable.just(make('client channel response'));
        return Flowable.error(new Error('not implemented'));
      }
}