/**
* @file CSQueue.h
*/

#pragma once
#ifndef _INC_CSQUEUE_H
#define _INC_CSQUEUE_H

#include "CSMemBlock.h"

/**
* @brief FIFO data buffer
*/
class CSQueueBytes
{
public:
	static const char * m_sClassName;

	/** @name Constructors, Destructor, Asign operator:
	 */
	///@{
	CSQueueBytes();
	~CSQueueBytes();
private:
	/**
	* @brief No copy on construction allowed.
    */
	CSQueueBytes(const CSQueueBytes& copy);
	/**
	* @brief No copy allowed.
    */
	CSQueueBytes& operator=(const CSQueueBytes& other);
	///@}
public:
	/** @name Capacity:
	 */
	///@{
	/**
	* @brief Get the element count from the queue.
	* @return Element count.
	*/
	size_t GetDataQty() const;
	///@}
	/** @name Modifiers:
	 */
	///@{
	/**
	* @brief Add an amount of data, resizing the buffer if needed.
	* @param pData pointer to the data to add.
	* @param iLen amount of data to add.
	*/
	void AddNewData( const byte * pData, size_t iLen );
	/**
	* @brief Increment the data counter.
	* @param iLen increment to add.
	*/
	void AddNewDataFinish( size_t iLen );
	/**
	* @brief Get the position to add an amount of data, resizing the buffer if needed.
	* @param iLen length needed.
	* @return pointer to the position where the data can be added.
	*/
	byte * AddNewDataLock( size_t iLen );
	/**
	* @brief Clear the queue.
	*/
	void Empty();
	/**
	* @brief Remove an amount of data from the queue.
	*
	* If amount is greater than current element count, all will be removed.
	* @param iSize amount of data to remove.
	*/
	void RemoveDataAmount( size_t iSize );
	/**
	* @brief Get the internal data pointer.
	* @return Pointer to internal data.
	*/
	const byte * RemoveDataLock() const;
	///@}

private:
	CSMemLenBlock m_Mem;	///< Data buffer.
	size_t m_iDataQty;	///< Item count of the data queue.
};

#endif // _INC_CSQUEUE_H