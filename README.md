# raytracer
At work, I am having to transition from doing 2d computer vision stuff to 3d computer vision stuff.
Although I have a strong background in maths and physics from my undergrad degree, I never took a class in computer graphics, classical computer vision etc.
My route into computer vision came from taking classes in deep learning and training 2D detection and tracking models etc.
Therefore I have been working through a ray tracing tutorial at <a href="https://raytracing.github.io/books/RayTracingInOneWeekend.html">this link</a> to try to 
build a deeper understanding of camera models, such that I'm comfortable manipulating the equations and implementing stuff myself. 
However, following the tutorial won't teach me much, because you're just typing code in instead of having to struggle to learn things yourself. 
Therefore I have come up with a AI assisted modification of this tutorial format. I am using cpp because it is the language we use for 3d computer vision.

## Workflow
* TLDR: Get Claude Fable to read the tutorial link and build implementation tasks for me (which I do myself, with no AI, not even for syntax lookup) so that I avoid just copying the code.
* Get it to cut out all the bits that aren't relevant to my goal of learning camera models (i.e material reflection, etc)
* Get it to break that roadmap down into step by step "assignments" with basic briefs and conceptual explanations, based on the tutorial sections
* Implement these tasks myself, with no AI help at all - occasionally reading the tutorial explanation but avoiding looking at the tutorial code
* Once I'm done, double check with the rendered image in the tutorial to make sure my implementation is good - as well as with Claude generated tests.
* To reiterate; I do not read the code in the tutorial or get Claude to help me implement it. I'm implementing it myself to build understanding.
* Read more about my philosophy of AI usage <a href="https://github.com/cravies/dotfiles/blob/main/prompt.md">In this repo</a>
