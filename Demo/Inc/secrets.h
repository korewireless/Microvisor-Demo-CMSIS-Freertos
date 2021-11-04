#ifndef SECRETS_H
#define SECRETS_H

// SIM_SID is not really secret, but is specific to your account
// AUTH_TOKEN _is_ secret, so take care not to push it to git server
#define AUTH_TOKEN "<output of `echo -n $TWILIO_KEY_SID:$TWILIO_KEY_SECRET | base64`>"
#define SIM_SID "HSXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#endif //SECRETS_H
