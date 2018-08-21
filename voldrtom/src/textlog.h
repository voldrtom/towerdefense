#ifndef TEXTLOG_H
#define TEXTLOG_H

/**
 * Class that represents text log
 */
struct CText_log {
/**
 * Constructor of the text log
 * @param id
 * @param health
 */
 	CText_log (	const int & id,
				const int & hp)
	:figureid(id), figurehp(hp) {}
	
	int figureid;
	int figurehp;
 };	

#endif
