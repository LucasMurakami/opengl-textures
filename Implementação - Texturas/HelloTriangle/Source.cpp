/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include "Sprite.h"

//GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//STB IMAGE
#include <stb_image.h>

using namespace std;
//using namespace glm; //para não usar glm::

//Classe para manipulação dos shaders
#include "Shader.h"

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
GLuint loadTexture(string texturePath);

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texturas", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");
			
	// Carregar texturas
	GLuint backgroundID = loadTexture("Textures/backgrounds/fantasy-set/PNG/Battleground2/bright/Battleground2.png");
	GLuint knightID = loadTexture("Textures/characters/PNG/Knight/Idle/idle1.png");
	GLuint mageID = loadTexture("Textures/characters/PNG/Mage/Idle/idle1.png");
	GLuint rogueID = loadTexture("Textures/characters/PNG/Rogue/Idle/idle1.png");
	GLuint blueSlimeID = loadTexture("Textures/blue_slime.png");

	//Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	// Ativa o shader
	shader.Use();

	//Matriz de projeção paralela ortográfica
	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));	
	
	// Criação dos sprites
	Sprite background(shader, backgroundID, glm::vec3(400.0f, 300.0f, 0.0f), glm::vec3(800.0f, 600.0f, 0.0f), 0.0f);
	Sprite mage(shader, mageID, glm::vec3(200.0f, 160.f, 0.0f), glm::vec3(200.0f, 200.0f, 0.0f), 0.0f);
	Sprite knight(shader, knightID, glm::vec3(300.0f, 200.f, 0.0f), glm::vec3(200.0f, 200.0f, 0.0f), 0.0f);
	Sprite rogue(shader, rogueID, glm::vec3(240.0f, 270.f, 0.0f), glm::vec3(200.0f, 200.0f, 0.0f), 0.0f);
	Sprite blueSlime(shader, blueSlimeID, glm::vec3(600.0f, 200.0f, 0.0f), glm::vec3(200.0f, 200.0f, 0.0f), 0.0f);

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); //unidades de tela: pixel

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		//Chamadas de desenho da cena
		background.draw();
		knight.draw();
		mage.draw();
		rogue.draw();
		blueSlime.draw();

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// Função para carregar a textura e retornar o ID da textura
GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na memória 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Configuração do parâmetro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Configuração do parâmetro FILTERING na minificação e magnificação da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Atributos básicos da imagem, largura, altura e número de canais de cores
	int width, height, nrChannels;
	// Habilita um flipagem vertical no carregamento da imagem
	stbi_set_flip_vertically_on_load(true);
	// Imagem
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			// Texturiza a imagem com o RGB
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		} 
		else //png
		{
			// Texturiza a imagem com o RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		// Permite o PNG mesclar com o fundo caso tenha fundo nulo
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Libera os dados da imagem
	stbi_image_free(data);
	// Desvincula a textura
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

