<?php

/**
 * @File
 * Block definition
 */

/**
 *Implements hook_block_info()
 */
function mailfish_block_info(){
    $blocks = array();

    $blocks['mailfish_subscribe'] = array(
        'info' => t('Mailfish subscribe form'),
    );
    return $blocks;
}



/**
 * Implements hook_block_view()
 */
function mailfish_block_view($delta = ''){
    $block = array();

    switch($delta){
        case 'mailfish_subscribe':
            $nid = arg(1);
            if (arg(0) == 'node' && $type = mailfish_check_node_id($nid)) {

                $types = variable_get('mailfish_types', array());
                if (!empty($types[$type]) && mailfish_get_node_enabled($nid)){

                    $block['subject'] = t('Sign up for this node');
                    $form = drupal_get_form('mailfish_email_form', $nid);
                    $block['content'] = theme('mailfish_block', array('form' => drupal_render($form)));

                    /**
                     * Other way to render the content is by using Renderable Arrays
                     *
                     * $block['content'] = array(
                     *    '#theme' => 'mailfish_block',
                     *    '#form' => drupal_render($form),
                     * );
                     */

                }


            }
            break;
    }

    return $block;
}

/**
 * Function to validate a node id
 * @param nid node id
 * @return Type of the node or FALSE if this is a valid node id
 */
function mailfish_check_node_id($nid){
    if(!is_numeric($nid)){
        return false;
    }
    $query = db_select('node','n');
    $query->fields('n', array('type'));
    $query->condition('n.nid', $nid);
    $type = $query->execute()->fetchField();
    if (!$type){
        return false;
    }
    else{
        return $type;
    }

}
