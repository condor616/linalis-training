<?php

/**
 * Admin settings form
 */
function youtrack_admin_settings_form($form, $form_state){
    $form['youtrack_endpoint'] = array(
        '#type' => 'textfield',
        '#title' => t('YouTrack Enpoint URL'),
        '#default_value' => '',
        '#size' => 60,
        '#maxlength' => 128,
        '#required' => TRUE,
    );

    return system_settings_form($form);

}