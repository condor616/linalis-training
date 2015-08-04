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
    );

    $form['youtrack_username'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#default_value' => variable_get('novartis_youtrack_username', array()),
        '#size' => 20,
        '#maxlength' => 128,
        '#required' => TRUE,
    );

    $form['youtrack_password'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#maxlength' => 64,
        '#size' => 20,
        '#required' => TRUE,
    );

    $form['youtrack_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save settings'),
    );

    return $form;

}



/**
 * hook_form_validate()
 */
function youtrack_admin_settings_form_validate($form, &$form_state){
    return TRUE;
}



/**
 * hook_form_submit()
 */
function youtrack_admin_settings_form_submit($form, &$form_state)
{
    drupal_set_message('Form submitted');

    variable_set('novartis_youtrack_endpoint', $form_state['input']['youtrack_endpoint']);
    variable_set('novartis_youtrack_username', $form_state['input']['youtrack_username']);
    variable_set('novartis_youtrack_password', $form_state['input']['youtrack_password']);



}