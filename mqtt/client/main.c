#include <mosquitto.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// to install mosquitto :
// git clone https://github.com/eclipse/mosquitto.git
// make
// make install

bool ackDone = false;

static void disconnectCallback ( struct mosquitto * mosq, void *   obj, int result )
{
}
static void publishCallback ( struct mosquitto * mosq, void *   obj, int result )
{
}
static void connectCallback ( struct mosquitto * mosq, void *   obj, int result )
{
	if ( !result )
	{
		ackDone = true;
	}
	else if ( result )
	{
		fprintf ( stderr, "%s\n", mosquitto_connack_string ( result ) );
	}
}

int main ( void )
{
	const int port = 8883;
	const char host[128] = "123.58.243.147";
	const char ca[] = "./cacert.pem";
	const char cert[] = "./client-cert.pem";
	const char key[] = "./client-key.pem";
	const char username[]="YS04G";
	const char password[]="wf070irify6b";
	struct mosquitto * mosq;
	int value = 0;
	int arg = 0;

	static int id = 0;

	if ( mosquitto_lib_init( ) )
	{
		return ( __LINE__ );
	}
	mosq = mosquitto_new ( "C_soft", true, NULL );

	if ( !mosq )
	{
		return ( __LINE__ );
	}


	mosquitto_connect_callback_set ( mosq, connectCallback );
	mosquitto_disconnect_callback_set ( mosq, disconnectCallback );
	mosquitto_publish_callback_set ( mosq, publishCallback );

	if ( mosquitto_will_set ( mosq, "/data", 16, "C client stoped", 0, 0 ) )
	{
		return ( __LINE__ );
	}

	value = MQTT_PROTOCOL_V31;
	if ( mosquitto_max_inflight_messages_set ( mosq, 20 ) ||
	 mosquitto_opts_set ( mosq, MOSQ_OPT_PROTOCOL_VERSION, &value ) )
	{
		return ( __LINE__ );
	}
	value = 0;

	if ( mosquitto_tls_opts_set ( mosq, 1, "tlsv1.2", NULL ) ||
		mosquitto_tls_set ( mosq, ca, NULL, cert, key, NULL ) ||
		mosquitto_tls_insecure_set ( mosq, true ) )
	{
		printf("tls set error\n");
		return ( __LINE__ );
	}

	if ( mosquitto_username_pw_set( mosq, username, password) == MOSQ_ERR_SUCCESS) {
		printf("username_pw_set success\n");
	}


	printf("mosquitto_connect\n");
	if ( mosquitto_connect ( mosq, host, port, 1000 ) )
	{
		printf("mosquitto_connect error\n");
		return ( __LINE__ );
	}
	else {
		printf("mosquitto_connect success\n");
	}



	printf("1111\n");
	while ( ackDone == false )
	{
	printf("1112\n");
		value = mosquitto_loop ( mosq, -1, 1 );
		if ( value )
		{
			printf ( "%d : %s\n", __LINE__, mosquitto_strerror ( value ) );
			return ( __LINE__ );
		}
		else
		{
	printf("1113\n");
			usleep ( 50000 );
		}
	}

	printf("1114\n");
	mosquitto_publish ( mosq, &id, "/data", 6, "C msg", 0, 0 );

	printf("1115\n");
	while( 1 )
	{
		sleep( 5 );
	}

	mosquitto_destroy ( mosq );
	mosquitto_lib_cleanup ( );

	return ( 0 );
}
