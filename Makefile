CC=gcc -g
CFLAGS=-c
HDR=-lpthread
final: main.o registration.o voting_request.o create_voting_req_form.o delete_voting_req_form.o voting_response.o create_registration_form.o delete_registration_form.o send_registration_form.o feedback_module.o feedback.o 
	$(CC) $^ $(HDR) -o $@
%.o:%.c
	$(CC) $(CFLAGS) $<
clean:
	rm *.o final

