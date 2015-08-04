<?php

/**
 * @File
 * Admin stuff
 */

/**
 * Admin setting form
 */
function mailfish_admin_settings_form($form, $form_state){
    $form['mailfish_types'] = array(
        '#title' => t('Content Types'),
        '#Description' => t('The content type to enable Maifish subscription for'),
        '#type' => 'checkboxes',
        '#options' => node_type_get_names(),
        '#default_value' => variable_get('mailfish_types', array()),
    );

    return system_settings_form($form);
}


/**
 * Reporting page callback
 */
function mailfish_signups(){

    //output will contain the HTML rendered by a theme_table
    $output = array(
        '#pre_render' => array('mailfish_intensive_rendering_part'),
        '#cache' => array(
            'keys' => array('mailfish_global_subscription'),
            'granularity' => DRUPAL_CACHE_PER_ROLE,
            'expire' =>  CACHE_PERMANENT,
        ),
    );

    // Get the schema
    $mailfish_schema = drupal_get_schema('mailfish');
    // Get the fields
    $mailfish_fields = array_keys($mailfish_schema['fields']);

    $query = db_select('mailfish','m')->extend('PagerDefault')->limit(3);
    $query->innerJoin('node','n','n.nid = m.nid');
    $query->innerJoin('users','u','u.uid = m.uid');
    $query->fields('m',$mailfish_fields);
    $query->fields('u',array('name'));
    $query->fields('n', array('title'));
    $query->orderBy('m.created', 'ASC');
    $results = $query->execute();

    //Build the header of the table
    $header = array(
        'User',
        'Node',
        'Email',
        'Created',
    );

    //Prepare the rows for the table
    $rows = array();
    foreach ($results as $result){
        $rows[] = array(
            !empty($result->name) ? l($result->name, 'user/' . $result->uid) : t('Anonymous'), //user with ID 0 will have no name ... use "anoymous in case"
            $result->title,
            $result->email,
            format_date($result->created, 'medium'),
        );
    }

    /*
    $uids = array_map(
        function($e){
            return $e->uid;
        },
            $results
    );

    $users = user_load_multiple($uids);
    dpm($users);
    */

    /* Option #1
     * Displaying results without using renderable arrays
     * $output = theme('table', array('header' => $header, 'rows' => $rows));
     * return $output;
    */

    //Options #2 -> use renderable arrays
    $table = array(
        '#theme' => 'table',
        '#rows' => $rows,
        '#header' => $header,
    );

    $output['title'] = array(
        '#theme' => 'html_tag',
        '#tag' => 'h2',
        '#value' => t('Subscription List'),
    );
    $output['table'] = $table;
    $output['pager'] = array('#theme' => 'pager');
    $output['list'] = array(
        '#theme' => 'item_list',
        '#items' => array('a','b','c'),
        '#title' => t('My ordered list'),
        '#type' => 'ul',
        '#attributes' => array('class' => array('my-list')),
    );


    return $output;
}

function mailfish_intensive_rendering_par($elements){

    return $elements;
}