import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import axios, { post } from 'axios';

export default class FileUploader extends Component {
    constructor(props) {
      super(props);
      this.state = {
        video: null,
        status: 0, // 1 is success, 2 is fail
        error: '',
      };
      this.handleSubmit = this.handleSubmit.bind(this);
      this.fileUpload = this.fileUpload.bind(this);
      this.fileChange = this.fileChange.bind(this);
    }

    handleSubmit(e) {
      e.preventDefault();
      console.log(this.state.video);
      this.fileUpload(this.state.video).then((response) => {
          console.log(response.data);
          this.setState({ status: 1 });
      })
      .catch( (error) => {
        console.log(error);
        this.setState({ status: 2, error: error });
      });
    }

    fileUpload(file) {
      const url = 'http://localhost:8000/api/uploadVideo';
      const formData = new FormData();
      formData.append('file', file);
      formData.append('token', this.props.token);
      const config = {
          headers: {
              'content-type': 'multipart/form-data'
          }
      }
      return post(url, formData, config)
    }

    fileChange (e) {
      //console.log(e.target.files[0]);
      this.setState({
        video: e.target.files[0]
      });
    }

    render() {
        return (
            <div className="container">
                <div className="row justify-content-center">
                    <div className="col-md-8">
                        <div className="card">
                            <div className="card-header">Upload Your Video</div>

                            <div className="card-body">
                                <form onSubmit={this.handleSubmit}>
                                  <input
                                    name="video"
                                    type="file"
                                    accept=".mp4"
                                    onChange={this.fileChange}
                                    required
                                  />
                                  <button
                                    type="submit"
                                    value="Submit"
                                    className="btn btn-primary">
                                    submit
                                  </button>
                                </form>
                            </div>
                        </div>
                        <div
                          className="alert alert-success mt-2"
                          hidden={this.state.status !== 1}
                        >
                          <strong>Success!</strong> Video uploaded
                        </div>
                        <div
                          className="alert alert-danger mt-2"
                          hidden={this.state.status !== 2}
                        >
                          <strong>Error!</strong> {this.state.error}
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}

if (document.getElementById('FileUploader')) {
    const element = document.getElementById('FileUploader');
    const props = Object.assign({}, element.dataset);
    ReactDOM.render(<FileUploader {...props} />, element);
}
