/**
  A very simple program to demonstrate how to consume a single message
  from an ActiveMQ queue using a C++ program.
*/
#include <stdio.h>
#include <string>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace cms;
using namespace std;

int main (int argc, char **argv)
  {
  // URI of the message broker -- set this to be appropriate for your broker
  string brokerURI =
        "tcp://localhost:61616";

  // JMS queue name
  string dest = "__test_destination";

  // Initialize CMS
  activemq::library::ActiveMQCPP::initializeLibrary();

  // Get a connection factory for the specified broker URI
  ActiveMQConnectionFactory* connectionFactory =
                new ActiveMQConnectionFactory (brokerURI);

  // Connect to the broker
  Connection *connection =
    connectionFactory->createConnection("admin" , "admin");

  connection->start();

  // Creation of the session, destination, and consumer are much
  //  the same as in the JMS API
  Session *session = connection->createSession (Session::AUTO_ACKNOWLEDGE);
  Destination *destination = session->createQueue (dest);
  MessageConsumer *consumer = session->createConsumer (destination);

  // Consume a text message
  TextMessage *m = (TextMessage*) consumer->receive();

  // Print the message contents. Note that c_str() gets the C
  //  represetntation of the C++ string object
  cout << "Received: " << m->getText() << endl;

  // Tidy up. Don't have to do this in Java :)
  delete m;
  delete destination;
  delete session;
  delete connection;
  delete connectionFactory;

  return 0;
  }
