<?php


//require_once(dirname(dirname(__FILE__)) . '/lib/php-iban/oophp-iban.php');


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
function commerce_sepa_iban_bic_form($fields = array(), $default = array(), $payment_method) {
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
		'#default_value' => $payment_method['settings']['details']['policy'],
		'#attributes' => array('autocomplete' => 'off'),
		'#field_suffix' => t('To debit your account via the SEPA direct debit, we require a SEPA direct debit mandate. This will sent to you via mail.')
  );
	
	// This is the "SEPA Direct Debit Mandate"
  $form['sepa']['mandate_check'] = array(
		'#type' => 'checkbox',
		'#title' => t('I authorise the creditor to send instructions to my bank to debit my account and my bank to debit my account. (electronic submission)'),
		'#required' => TRUE,
  );

  return $form;
}

/**
 * Validates the IBAN with php-iban loaded with Libraries
 * copy php-iban to sites/all/libraries   
 */
function commerce_sepa_iban_bic_validate($details, $settings) {
	$prefix = implode('][', $settings['form_parents']) . '][';
	if (($library = libraries_detect('php-iban')) && !empty($library['installed'])) {
		$library = libraries_load('php-iban');  
		if(verify_iban($details['iban'])) return TRUE;   
			form_set_error($prefix . 'type', t('IBAN is not valid.'));
			return FALSE;	
		}
		else {
			$error = $library['error'];
			$error_message = $library['error message'];
		}
	}




