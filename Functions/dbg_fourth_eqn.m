function M = dbg_fourth_eqn(J,O,Od)
M = J*Od+hat(O)*(J*O);
end