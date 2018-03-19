import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import FileUploader from './FileUploader';
import VideoList from './VideoList';
import axios, { post } from 'axios';
import { status } from '../util/status';

export default class Home extends Component {
    constructor(props) {
        super(props);
        this.state = {
            videos: [],
            error: null,
        };
        this.updateVideos = this.updateVideos.bind(this);
        this.handleSuccess = this.handleSuccess.bind(this);
    }

    componentDidMount() {
      this.handleSuccess();
    }

    handleSuccess() {
        this.updateVideos().then((response) => {
            console.log(response.data.data);
            this.setState({ videos: response.data.data });
        })
        .catch((error) => {
            console.log(error);
            this.setState({ error: error.response.data });
        });
    }

    updateVideos() {
      const url = 'http://localhost:8000/api/originalVideos';
      const formData = new FormData();
      formData.append('token', this.props.token);
      const config = {
          headers: {
              'content-type': 'multipart/form-data'
          }
      }
      return post(url, formData, config)
    }

    render() {
        return (
          <div className="container">
              <div className="row justify-content-center">
                  <FileUploader
                      token={this.props.token}
                      handleSuccess={this.handleSuccess}
                  />
                  <VideoList videos={this.state.videos} />
              </div>
          </div>
        );
    }
}

if (document.getElementById('Home')) {
    const element = document.getElementById('Home');
    const props = Object.assign({}, element.dataset);
    ReactDOM.render(<Home {...props} />, element);
}
