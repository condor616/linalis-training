<?php

/**
 * Admin settings form
 */
function youtrack_admin_settings_form($form, $form_state){

    $form['youtrack_endpoint'] = array(
        '#type' => 'textfield',
        '#title' => t('YouTrack Enpoint URL'),
        '#default_value' => variable_get('novartis_youtrack_endpoint', array()),
        '#size' => 60,
        '#maxlength' => 128,
        '#required' => TRUE,
        '#attributes' => array('autocomplete' => 'off'),
    );

    $form['youtrack_username'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#default_value' => variable_get('novartis_youtrack_username', array()),
        '#size' => 20,
        '#maxlength' => 128,
        //'#required' => TRUE,
        '#attributes' => array('autocomplete' => 'off'),
    );

    $form['youtrack_password'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#maxlength' => 64,
        '#size' => 20,
        //'#required' => TRUE,
        '#attributes' => array('autocomplete' => 'off'),
    );

    $form['youtrack_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save settings'),
    );

    $form['youtrack_reset'] = array(
        '#type' => 'submit',
        '#value' => t('Reset'),
        '#submit' => array('youtrack_admin_settings_form_reset'),
    );

    return $form;

}


/**
 * Custom youtrack_admin_settings_form_reset function
 */
function youtrack_admin_settings_form_reset($form, &$form_state){
    variable_del('novartis_youtrack_endpoint');
    variable_del('novartis_youtrack_username');
    variable_del('novartis_youtrack_password');
}


/**
 * hook_form_validate()
 */
function youtrack_admin_settings_form_validate($form, &$form_state){

    /*
     * Check if URL is correct
     */
    if (!valid_url($form_state['input']['youtrack_endpoint'], TRUE)){
        form_set_error('youtrack_endpoint', t("%endpoint is an invalid endpoint", array('%endpoint'=>$form_state['input']['youtrack_endpoint'])));
    }
    /*
     * Check that Username is not empty
     */
    if (empty($form_state['input']['youtrack_username'])){
        form_set_error('youtrack_username', t("Username cannot be empty"));
    }
    /**
     * Check that password is not empty
     */
    if (empty($form_state['input']['youtrack_password'])){
        form_set_error('youtrack_passwird', t("Password cannot be empty"));
    }
}



/**
 * hook_form_submit()
 */
function youtrack_admin_settings_form_submit($form, &$form_state)
{
    variable_set('novartis_youtrack_endpoint', $form_state['input']['youtrack_endpoint']);
    variable_set('novartis_youtrack_username', $form_state['input']['youtrack_username']);
    variable_set('novartis_youtrack_password', $form_state['input']['youtrack_password']);

    /*
     * Try to login
     */
    novartis_youtrack_try_login(
        variable_get('novartis_youtrack_endpoint', array()),
        variable_get('novartis_youtrack_username', array()),
        variable_get('novartis_youtrack_password', array())
    );
}


function novartis_youtrack_try_login($url, $username, $password){

    $data = 'login=' . $username . '&password=' . $password;
    $url .= '/rest/user/login';

    $options = array(
        'method' => 'POST',
        'data' => $data,
        'timeout' => 15,
        'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
    );

    $result = drupal_http_request($url, $options);
    dpm($result);

    switch ($result->code){
        case '403':
            drupal_set_message(t('HTTP Code: %code. %text', array('%code' => $result->code, '%text' => $result->error)), 'error');
            break;
        case '404':
            drupal_set_message(t('HTTP Code: %code. %text', array('%code' => $result->code, '%text' => $result->error)), 'error');
            break;
        case '200':
            drupal_set_message(t('HTTP Code: %code.', array('%code' => $result->code)), 'status');
            drupal_set_message(t('Response: %response', array('%response' => $result->data)));
            break;
    }
}