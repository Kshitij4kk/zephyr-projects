/**
 * @file main.c
 * @brief Application entry point
 * @author Kshitij Kumar <kshitij9192@gmail.com>
*/

#include <tinycrypt/constants.h>
#include <tinycrypt/ecc.h>
#include <tinycrypt/ecc_dsa.h>
#include <sys/base64.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int default_CSPRNG(uint8_t *dest, unsigned int size) {}

/*
* Refer to https://cryptobook.nakov.com/asymmetric-key-ciphers/elliptic-curve-cryptography-ecc
*/

/* TODO : Use random number generator to get a private key (32 bytes long). Currently for POC, having a fixed private key here. */
static uECC_word_t private_key[8] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};

/**/
static uECC_word_t public_key[16];


int main(void)
{
	int status;

	/*** Get public key from the private key ***/
	status = uECC_compute_public_key(&private_key[0], &public_key[0], uECC_secp256r1());
	if( status == 1)
	{
		/* TODO : Log/Print : Public key computation successful */
	}
	else
	{
		/* TODO : Log/Print : Public key computation failed */
		exit(1);
	}
	
	/* Sample header of jwt token. Play with these here for testing.*/
	char* jwt_header = "\n{\n\t\"alg\": \"ES256\",\n\t\"typ\": \"JWT\"\n}";

	/* Sample jwt payload. Play with these here for testing. */
	char* jwt_payload = "\n{\n\t\"sub\": \"1234567890\",\n\t\"name\": \"John Doe\",\n\t\"admin\": \"true\"\n}";


	/* Converting jwt header and payload to base64 base64_encode */
	uint8_t encoded_header[100], encoded_payload[100];
	int enc_header_len, enc_payload_len;
	if( base64_encode(&encoded_header[0], 100, &enc_header_len, &jwt_header[0], (size_t)strlen(jwt_header)) == 0)
	{
		/* TODO : Log/Print : Successfully encoded to base64 */
	}
	else
	{
		/* TODO : Log/Print : base64 encoding failed */
		exit(2);
	}
	
	if( base64_encode(&encoded_payload[0], 100, enc_payload_len, &jwt_payload[0], (size_t)strlen(jwt_payload)) == 0)
	{
		/* TODO : Log/Print : Successfully encoded to base64 */
	}
	else
	{
		/* TODO : Log/Print : base64 encoding failed */
		exit(3);
	}
	
	/*Since encoding is done, lets create the final buffer ("header"."payload" format) which needs to be signed */
	uint8_t raw_buffer[enc_header_len + enc_payload_len + 1];
	memcpy(raw_buffer, &encoded_header[0], enc_header_len);
	memset(raw_buffer+enc_header_len, '.', 1);
	memcpy(raw_buffer+enc_header_len+1, &encoded_payload, enc_payload_len);
	
	/*** Lets create signature for this raw buffer ***/
	uint8_t ecc_signature[64];
	if( uECC_sign(&private_key[0], &raw_buffer[0], strlen(raw_buffer), &ecc_signature[0], uECC_secp256r1()) == TC_CRYPTO_SUCCESS)
	{
		/* TODO : Log/Print : Signature created successfully*/
	}
	else
	{
		/* TODO : Log/Print : Signature creation failed */
		exit(4);
	}
	
	/*** Verifying the signature part ***/
	if( uECC_verify(&public_key[0], &raw_buffer[0], strlen(raw_buffer), &ecc_signature[0], uECC_secp256r1()) == TC_CRYPTO_SUCCESS)
	{
		/* TODO : Log/Print : Signature verified successfully*/
	}
	else
	{
		/* TODO : Log/Print : Signature verification failed */
		exit(4);
	}
	
}

