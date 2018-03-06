import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import axios from 'axios';

export default class FileUploader extends Component {
    constructor(props) {
      super(props);
      this.state = {video: null};
    }

    handleSubmit(e) {
      e.preventDefault();
      console.log(this.state.video);
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
                                <form onSubmit={this.handleSubmit.bind(this)}>
                                  <input
                                    name="video"
                                    type="file"
                                    accept=".mp4"
                                    form-control-file
                                    onChange={this.fileChange.bind(this)}
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
                    </div>
                </div>
            </div>
        );
    }
}

if (document.getElementById('FileUploader')) {
    ReactDOM.render(<FileUploader />, document.getElementById('FileUploader'));
}
