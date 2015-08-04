<?php

/**
 * @File
 * API for mailfish module
 */

function mailfish_get_node_enabled($nid){
    if (is_numeric($nid)){
        $query = db_select('mailfish_enabled', 'me');
        $query->fields('me', array('nid'));
        $query->condition('me.nid', $nid);
        $results = $query->execute()->fetchField();

        if ($results)
            return TRUE;
    }
    return FALSE;
}


function mailfish_set_node_enabled($nid){
    if (is_numeric($nid)){
        $query = db_insert('mailfish_enabled');
        $query->fields(array('nid' => $nid));
        $query->execute();
    }
}


function mailfish_delete_node_enabled($nid){
    if (is_numeric($nid)){
        $query = db_delete('mailfish_enabled');
        $query->condition('nid', $nid);
        $query->execute();
    }
}