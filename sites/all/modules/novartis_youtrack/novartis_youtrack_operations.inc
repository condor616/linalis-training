<?php

function youtrack_show_operations(){

    $items = array(
        l(t('Get list of projects'),
            'admin/config/content/youtrack/operations/get-projects',
            array(
                'attributes' => array('class' => 'about-link another-class'),
                'html' => TRUE,
            )
        ),
        l(t('Get list of issues for a given project'),
            'admin/config/content/youtrack/operations/get-issues-by-project',
            array(
                'attributes' => array('class' => 'about-link another-class'),
                'html' => TRUE,
            )
        ),

    );

    $output['list'] = array(
        '#theme' => 'item_list',
        '#items' => $items,
        '#title' => t('Operations'),
        '#type' => 'ul',
        '#attributes' => array('class' => array('my-list')),
    );


    return $output;
}