# Commerce Sepa

Provides a simple SEPA payment method with IBAN validation for Drupal Commerce. The IBAN validation is made with php-iban from https://code.google.com/p/php-iban. 
Once enabled customer can choose SEPA-Payment and add their IBAN and BIC to the order. After completing the order a mail with the SEPA Direct Debit Mandate is sent 
to the customer with all necessary information (creditor identifier, mandate reference).
