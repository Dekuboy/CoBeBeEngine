namespace cobebe
{
	class Core;

	/**
	* \brief Holds deltaTime and screen size
	*/
	class Environment
	{
	public:
		Environment();

		/**
		* \brief Retrives deltaTime
		*/
		const float getDeltaTime();
		/**
		* \brief Retrieves screen width
		*/
		const int getWidth();
		/**
		* \brief Retrieves screen height
		*/
		const int getHeight();

	private:
		friend class Core;

		float m_deltaTime; ///< Maintains framerate
		int m_width; ///< Screen width
		int m_height; ///< Screen height

	};
}