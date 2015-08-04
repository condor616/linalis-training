<?php

/**
 * @File
 * Node operations
 */


/*
 * Implements hook_node_load()
 */
function mailfish_node_load($nodes, $types){
    foreach ($nodes as $node){
        $node->mailfish_enabled = mailfish_get_node_enabled($node->nid);
    }
}


/*
 * Implements hook_node_update()
 */
function mailfish_node_update($node){
    if ($node->mailfish_enabled){
        mailfish_set_node_enabled($node->nid);
    }
    else{
        mailfish_delete_node_enabled($node->nid);
    }
}


/**
 * Implements hook_node_delete()
 */
function mailfish_node_delete($node)
{
    mailfish_delete_node_enabled($node->nid);
}



/*
 * Implements hook_node_insert()
 */
function mailfish_node_insert($node){
    if ($node->mailfish_enabled){
        mailfish_set_node_enabled($node->nid);
    }
}