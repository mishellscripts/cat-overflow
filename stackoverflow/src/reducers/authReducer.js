import { AUTH_USER,
         UNAUTH_USER,
         AUTH_ERROR,
         REGISTER_ERROR,
         REGISTER_STATUS,
       } from '../actions/types';
import { status } from '../util/status';

const INITIAL_STATE = {
  login_error: null,
  register_error: null,
  register_status: status.WAITING,
  fetching_user: false,
  user: null,
  fetch_user_error: null,
}

export default function (state = INITIAL_STATE, action) {
  switch(action.type) {
    case AUTH_USER:
      return { ...state, token: action.payload , register_error: null, error: null};
    case UNAUTH_USER:
      return { ...state, token: null, user: null };
    case AUTH_ERROR:
      return { ...state, login_error: action.payload };
    case REGISTER_ERROR:
      return { ...state, register_error: action.payload };
    case REGISTER_STATUS:
      return { ...state, register_status: action.payload };
    default:
      return state;
  }
}
