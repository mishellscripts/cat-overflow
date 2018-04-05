import React, { Component } from 'react';
import { Form, Input, Button } from 'semantic-ui-react';
import { Field, reduxForm } from 'redux-form';
import { connect } from 'react-redux';
import { withRouter } from 'react-router-dom';
import '../styles/index.css';

class Home extends Component {
  username = value =>
    value && !/^[A-Z0-9]+$/i.test(value)
      ? 'Invalid username'
      : undefined;

  handleFormSubmit(formProps) {
    console.log(formProps);
  }

  renderField = ({
    input: { onChange },
    label,
    meta: { touched, error, warning }
  }) => (
      <Form.Field
          label={label}
          control={Input}
          type={label==='password' ? 'password' : 'text'}
          onChange={onChange}
          error={error}
      />
  );

  render() {
    const { handleSubmit, submitting } = this.props;
    return (
        <div className="page">
          <div className="title">
            welcome
          </div>
          <div className="body">
            <div className="login">
              <Form onSubmit={handleSubmit(this.handleFormSubmit.bind(this))}>
                  <Field
                    name="username"
                    label="username"
                    component={this.renderField}
                    validate={this.username}
                  />
                  <Field
                    name="password"
                    label="password"
                    component={this.renderField}
                  />
                  <Form.Button
                    fluid
                    color='red'
                    type="submit"
                    disabled={submitting}
                    content='Sign In'
                  />
                  <Button
                    fluid
                    color='blue'
                    disabled={submitting}
                    content='Create Account'
                  />
              </Form>
            </div>
          </div>
        </div>
    );
  }
}

Home = reduxForm({
  form: 'login'
})(Home);

function mapStateToProps(state) {
  return {
    errorMessage: state.auth.login_error,
  };
}

export default withRouter(connect(null, {})(Home));
