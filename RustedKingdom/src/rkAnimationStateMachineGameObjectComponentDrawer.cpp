#include "rkAnimationStateMachineGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkAnimationState.h"
#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationStateMachineGameObjectComponentDrawer::
    AnimationStateMachineGameObjectComponentDrawer()
    : AGameObjectComponentDrawer("Animation State Machine")
  {
  }

  AnimationStateMachineGameObjectComponentDrawer::
    ~AnimationStateMachineGameObjectComponentDrawer()
  {
  }

  void AnimationStateMachineGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    AnimationStateMachineComponent& asmComponent =
      static_cast<AnimationStateMachineComponent&>(component);

    drawAnimationState(asmComponent.getCurrentState());
  }

  void AnimationStateMachineGameObjectComponentDrawer::drawAnimationState(
    const AnimationState* state
  )
  {
    if (!state)
    {
      ImGui::Text("Current State: None");
      return;
    }

    ImGui::Text("Current State: %s", state->getKey().c_str());
    if (ImGui::CollapsingHeader("Animation State Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
      if (ImGui::TreeNode("Transitions:"))
      {
        const Vector<UniquePtr<AnimationStateTransition>>& transitions =
          state->getTransitions();

        Int32 index = 0;
        for(const UniquePtr<AnimationStateTransition>& transition : transitions)
        {
          String nodeLabel = String::Format("Transition #%d", index++);
          if (ImGui::TreeNode(nodeLabel.c_str()))
          {
            ImGui::Text("From: %s", transition->getFromState().getKey().c_str());
            ImGui::Text("To: %s", transition->getToState().getKey().c_str());
            ImGui::TreePop();
          }
        }

        ImGui::TreePop();
      }
    }
  }
}