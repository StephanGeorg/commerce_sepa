# Commerce SEPA

Provides a simple SEPA payment method with IBAN validation for Drupal Commerce. The IBAN validation is made with php-iban from https://code.google.com/p/php-iban. 
Once enabled customer can choose SEPA-Payment and add their IBAN and BIC to the order. After completing the order a mail with the SEPA Direct Debit Mandate is sent 
to the customer with all necessary information (creditor identifier, mandate reference).

## Installation

1. Install and enable module
2. Copy php-iban to sites/all/libraries

## Configuration

You can edit the SEPA mandate for confirmation in the payment settings. 

1. Go to the payment methods admin/commerce/config/payment-methods
2. Open "SEPA Payment"
3. Click the Action "Enable payment method: SEPA Payment"
4. Go to the "Payment settings" and edit the "SEPA Direct Debit Mandate"

You can also edit the SEPA mandate which is sent to the client

1. Go to the Rules UI admin/config/workflow/rules
2. Open the rule "Sent SEPA Direct Debit Mandate"
3. Click the Action "Send mail"
4. Edit the Message value 
