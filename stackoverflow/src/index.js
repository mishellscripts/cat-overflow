import React from 'react';
import ReactDOM from 'react-dom';
import registerServiceWorker from './registerServiceWorker';
import { Router, Route, Switch } from 'react-router-dom';
import { applyMiddleware, createStore, compose } from 'redux';
import { Provider } from 'react-redux';
import thunk from 'redux-thunk';
import rootReducer from './reducers/index';
import Home from './components/Home';
import history from './history';
import './styles/index.css';
import 'semantic-ui-css/semantic.min.css';

const composeEnhancers = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__ || compose;
export const store = createStore(rootReducer, /* preloadedState, */ composeEnhancers(
    applyMiddleware(thunk)
  ));

const Root = () => {
  return (
    <Provider store={store}>
        <Router history={history}>
          <Switch>
            <Route exact path="/" component={Home}/>
          </Switch>
        </Router>
    </Provider>
  );
}

ReactDOM.render(<Root />, document.getElementById('root'));

registerServiceWorker();
