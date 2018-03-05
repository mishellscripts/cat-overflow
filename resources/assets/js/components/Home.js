import React, { Component } from 'react';
import ReactDOM from 'react-dom';

class Home extends Component {

  render() {
    return (
        <h1>Welcome</h1>
    );
  }
  
}

ReactDOM.render(<Home />, document.getElementById("root"));