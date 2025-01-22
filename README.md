# Real-Time-Message-Scheduling-on-Automotive-CAN-Bus
In this project I have done message scheduling on Automotive CAN bus considering message priorities.

1. In this Project I did scheduling of messages over the CAN bus. Different messages are getting invoked from various sources inside the system. We need to schedule them over the bandwidth limited CAN bus. We can observe that when the bandwidth is less most of the messages cant be scheduled and hence many message can’t be reached to the destination within their required deadline.

2. Narrow bandwidth is the reason for poor scheduling of messages. But for already deployed systems we can’t do any hardware related changes so it is feasible to do it using software. In this assignment we understood the potential reasons of poor scheduling and how piggybacking can help us in achieving it.
   
3. In piggybacking we collect the messages from same sources into same set and schedule the complete set at a time. This helps in reducing the delays for high priority messages and also improves bus utilisation factor.

   
Steps to Run the Code :
1. Keep the source_code.cpp file and 2 text files ie Normal.txt and Piggybacked.txt in the same folder.
2. Run the cpp file.
3. It will ask to insert the MAC (Message Authentication Code) size, MAC generation time and MAC verification time.
4. For 1st task all values should be 0.
5. For 2nd Task give values according to requirement.
6. At a time both normal scheduling and piggybacked scheduling results will be generated.

In the submission I have included 2 text files. One (Normal.txt) representing the normal scheduling details while other (Piggybacked.txt) represents the piggybacked version of these message signals.


For more details about this project go through report.pdf file.
