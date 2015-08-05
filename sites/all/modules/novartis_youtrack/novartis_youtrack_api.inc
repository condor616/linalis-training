<?php

/**
 * youtrack_get_projects()
 */
function youtrack_get_projects(){
    $url = variable_get('novartis_youtrack_endpoint', array());
    $url .= '/rest/project/all';

    $options = array(
        'method' => 'GET',
        'timeout' => 15,
        'headers' => array(),
    );

    $result = drupal_http_request($url, $options);
    //return(dpm($result));

    /*
     * Transform the XML into PHP object
     */
    $xml = json_decode(json_encode((array) simplexml_load_string($result->data)), 1);
    //dpm($xml['project']);

    /*
     * Add the project to an array
     */
    $projects = array();
    foreach ($xml['project'] as $key=>$value) {
        $projects[$xml['project'][$key]['@attributes']['shortName']] = $xml['project'][$key]['@attributes']['name'];
    }

    $output = array(
        '#theme' => 'item_list',
        '#items' => $projects,
        '#title' => t('Projects'),
        '#type' => 'ul',
        '#attributes' => array('class' => array('my-list')),
    );


    return $output;
}



/*
 * youtrack_get_issues_by_project()
 */
function youtrack_get_issues_by_project(){
    return "TEST";
}