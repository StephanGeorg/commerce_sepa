<?php


require_once(dirname(dirname(__FILE__)) . '/lib/php-iban/oophp-iban.php');


/**
 * @file
 * IBAN/BIC helper functions for Drupal commerce_sepa.
 */

/**
 * Returns a set of SEPA form elements that payment method modules can
 *   incorporate into their submission form callbacks.
 *
 * @param $fields
 *   An array specifying the CC fields that should be included on the form; the
 *     card number and expiration date fields are always present.
 * @param $default
 *   An array of default values for the available CC fields.
 */
function commerce_sepa_iban_bic_form($fields = array(), $default = array()) {
  // Merge default values into the default array.
  $default += array(
		'iban' => '',
		'bic'	=> '',
		'owner'	=> '',
  );

  $form['sepa'] = array(
    '#tree' => TRUE,
    '#attached' => array(
      //'css' => array(drupal_get_path('module', 'commerce_sepa') . '/theme/commerce_payment.theme.css'),
    ),
  );

 	
	// Always add a field for the IBAN number.
  $form['sepa']['iban'] = array(
    '#type' => 'textfield',
    '#title' => t('IBAN'),
    '#default_value' => '',
    '#attributes' => array('autocomplete' => 'off'),
    '#required' => TRUE,
    '#maxlength' => 34,
    '#size' => 34,
  );
	
	// Always add a field for the BIC number.
  $form['sepa']['bic'] = array(
    '#type' => 'textfield',
    '#title' => t('BIC'),
    '#default_value' => '',
    '#attributes' => array('autocomplete' => 'off'),
    '#required' => TRUE,
    '#maxlength' => 34,
    '#size' => 34,
  );
		
	// This is the "SEPA Direct Debit Mandate"
	// Text should be dynamic ??? 
  $form['sepa']['mandate'] = array(
		'#type' => 'textarea',
		'#title' => t('SEPA Direct Debit Mandate'),
		'#default_value' => 'This is the SEPA Direct Debit Mandate',
		'#attributes' => array('autocomplete' => 'off'),
  );
	
	// This is the "SEPA Direct Debit Mandate"
  $form['sepa']['mandate_check'] = array(
		'#type' => 'checkbox',
		'#title' => t('SEPA Direct Debit Mandate'),
		'#options' => t('By signing this mandate form, you authorise to send instructions to your bank to debit your account.'),
		'#required' => TRUE,
  );

  return $form;
}


/**
 * Validates the IBAN with php-iban
 *   
 */
function commerce_sepa_iban_bic_validate($details, $settings) {
	$prefix = implode('][', $settings['form_parents']) . '][';
	$myIban = new IBAN($details['iban']);
	if($myIban->Verify()) {
		return TRUE; 
	} 
	form_set_error($prefix . 'type', t('IBAN is not valid.'));
	return FALSE;
}




