import React from 'react';
import { rsocketService } from '../services/rsocketService';
const rs = new  rsocketService();
export const rsService = React.createContext(rs);