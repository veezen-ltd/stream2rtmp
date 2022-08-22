import React from 'react';
import ReactDOM from 'react-dom';
import { UserMediaProvider } from '@vardius/react-user-media';

import App from './App';

ReactDOM.render(
    <UserMediaProvider constraints={{ audio: true, video: true }}>
        <App />
    </UserMediaProvider>,
    document.getElementById("root")
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals

